#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StructuresDef.h"
#include "OfficerFunctions.h"
#include "VoterFunctions.h"
#include "CandidateFunctions.h"
#include "VoterPanel.h"

void
enterVoterPanel(Officer *officerArray, int officerSize, Voter *voterArray, int votersSize, Candidate *candidateArray,
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

            printf("\nLast Name:");
            char lNameAttempt[20];
            scanf("%s", &lNameAttempt);

            if(strcmp(fNameAttempt, voterArray[i].fName) == 0
            && strcmp(lNameAttempt, voterArray[i].lName) == 0) {
                printf("\nCredentials Accepted\n"
                       "You may now cast your vote\n");


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
}