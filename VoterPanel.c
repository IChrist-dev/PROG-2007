#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StructuresDef.h"
#include "OfficerFunctions.h"
#include "VoterFunctions.h"
#include "CandidateFunctions.h"
#include "VoterPanel.h"

void enterVoterPanel(Officer *officerArray, int officerSize, Voter *voterArray, int votersSize, Candidate *candidateArray,
                int candidatesSize) {
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    printf("\n---Voting Panel---\n");
    char input[256];
    int voterMenuChoice;
    int loginAttempt;
    bool voterMenuSwitch = false;
    do {
        printf("\nMenu\n"
               "1. Cast Vote\n"
               "2. Enter Admin Mode\n");
        fgets(input, sizeof(input), stdin);
        voterMenuChoice = strtol(input, NULL, 10);

        switch (voterMenuChoice) {
            case 1:
                castVote(voterArray, votersSize, candidateArray, candidatesSize);
                break;

            case 2:
                loginAttempt = officerLogin(officerArray, officerSize);
                if (loginAttempt == 0) {
                    //Successful officer login. Go back to the Admin panel
                    voterMenuSwitch = true;
                    break;

                } else if (loginAttempt == 1) {
                    //Unsuccessful login, stays in the voter panel
                    printf("\nYou are not authorized to access the Admin panel.\n");
                    break;
                }
            default:
                //Input validation
                printf("\nThat choice was not listed. Please try again.\n");
                break;

        }
    } while (!voterMenuSwitch);
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);
    printf("\nReturning to Admin Panel...\n");
}

//Function to validate voters and allow them to cast votes
void castVote(Voter *voterArray, int votersSize, Candidate *candidateArray, int candidatesSize) {
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    printf("\nPlease enter your unique key code:");
    char keyCodeAttempt[6];
    scanf("%s", &keyCodeAttempt);

    bool keyCodeFound = false;

    //Check if provided keycode is valid
    for(int i=0; i<votersSize; i++) {
        if(strcmp(keyCodeAttempt, voterArray[i].keyCode) == 0) {
            //Match found
            keyCodeFound = true;
            printf("\nPlease provide your name so we can confirm this key code belongs to you.\n"
                   "First Name:");
            char fNameAttempt[20];
            scanf("%s", &fNameAttempt);

            printf("Last Name:");
            char lNameAttempt[20];
            scanf("%s", &lNameAttempt);


            if(strcmp(fNameAttempt, voterArray[i].fName) == 0
            && strcmp(lNameAttempt, voterArray[i].lName) == 0) {

                //Check if person has voted. Reject them if true
                if(voterArray[i].hasVoted) {
                    printf("\nYou are recorded as having already voted.\n"
                           "You may not vote multiple times.\n"
                           "\nNow returning to the Voting menu...");
                    break;
                }
                printf("\nCredentials Accepted\n"
                       "You may now cast your vote\n");

                bool finalVote = false;

                //index for candidateArray
                int j;

                do {
                    //Present all the candidates to the voter
                    printf("Candidate options\n"
                           "Option #\tName\t\t\tParty\n");
                    for(j = 0; j<candidatesSize; j++) {
                        printf("%d.\t\t%s %s\t\t%s\n",
                               j+1,
                               candidateArray[j].fName,
                               candidateArray[j].lName,
                               candidateArray[j].party);
                    }
                    //Option to exit the voting process early
                    printf("0. Return to Voting Panel");

                    printf("\nSelected Option #:");
                    int selectedOption;
                    scanf("%d", &selectedOption);

                    //Ensure no lingering inputs are in the buffer
                    fflush(stdin);

                    if(selectedOption == '0') {
                        //Returns to the voting panel
                        break;
                    }


                    //Confirm selection
                    printf("You have chosen to vote for %s %s of the %s party.\n"
                           "Are you certain? Y/N\n",
                           candidateArray[selectedOption].fName,
                           candidateArray[selectedOption].lName,
                           candidateArray[selectedOption].party);
                    char confirmVote;
                    scanf("%c", &confirmVote);

                    if(confirmVote == 'Y' || confirmVote == 'y') {
                        //Voter has decided on their choice
                        finalVote = true;

                        //Correct option # to align with array index
                        selectedOption--;

                        //Add vote to appropriate candidate's count
                        candidateArray[selectedOption].voteCount++;
                        //Save voter's chosen party as a variable in their structure
                        strcpy(voterArray[i].candidateChoice, candidateArray[i].party);
                        //Mark the voter as having voted, so they cannot cast multiple votes
                        voterArray[i].hasVoted = true;

                        printf("\nYour vote has been recorded\nThank you\n");
                    } else {
                        printf("\nThis selection will be erased. You may see the options again.\n");
                    }
                } while(!finalVote);


            } else {
                printf("\nThe name you have provided does not match your key code.\n"
                       "Please restart the ballot casting process or request assistance from a Voting Officer.");
                break;
            }
        }
    }
    if(!keyCodeFound) {
        printf("\n That key code could not be found. Please try again or request assistance from a Voting Officer.");
    }

    //Ensure no lingering inputs are in the buffer
    fflush(stdin);
}