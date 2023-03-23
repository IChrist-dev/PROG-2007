#include <stdio.h>
#include <string.h>
#include "StructuresDef.h"
#include "CandidateFunctions.h"

//Function to add information to fixed-size Candidate array
void addCandidates(Candidate *candidateArray, int candidatesSize) {
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    printf("\nWelcome to the Candidate input page.");
    printf("\n---Candidate Input Should Only Be Performed Once---\n");


    //Sub-process to exit before optional data input
    printf("\nPress [x] to leave this page.\n"
           "Press [y] to start entering candidate information.\n");
    char stayGo;
    scanf(" %c", &stayGo);

    if (stayGo == 'x') {
        //Ensure no lingering inputs are in the buffer
        fflush(stdin);
        return;
    } else if (stayGo == 'y') {
        for (int i = 0; i < candidatesSize; i++) {
            printf("\n---Candidate %d---", (i + 1));

            printf("\nFirst name:");
            scanf("%s", candidateArray[i].fName);

            printf("Last name:");
            scanf("%s", candidateArray[i].lName);

            printf("Party:");
            scanf("%s", candidateArray[i].party);
            printf("\nCandidate %d has been added.\n", (i + 1));

            //Newly added candidate vote count starts at 0
            candidateArray[i].voteCount = 0;
        }
    }
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);
}

//Function to edit Candidate information
void editCandidates(Candidate *candidateArray, int candidatesSize) {
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    printf("\nWelcome to the candidate editing page.\n");
    printf("Enter the party of the candidate you would like to edit:");
    char inputPartyName[30];
    scanf("%s", &inputPartyName);

    //Search through the candidate array for a party match
    for (int i=0; i <candidatesSize; i++) {
        if(strcmp(inputPartyName, candidateArray[i].party) == 0) {

            int editChoice;
            do {
                printf("Current Candidate Details:\n"
                       "1. Name: %s %s\n"
                       "2. Party: %s\n"
                       "3. Vote Count: %d\n"
                       "0. Return to Admin Menu\n"
                       "\nWhich would you like to edit?\n",
                       candidateArray[i].fName,
                       candidateArray[i].lName,
                       candidateArray[i].party,
                       candidateArray[i].voteCount);
                scanf("%d", &editChoice);

                switch(editChoice) {
                    case 1:
                        printf("\nNew First Name:");
                        scanf("%s", candidateArray[i].fName);

                        printf("New Last Name:");
                        scanf("%s", candidateArray[i].lName);
                        printf("\nName edit complete.\n");
                        break;
                    case 2:
                        printf("\nNew Party Name:");
                        scanf("%s", candidateArray[i].party);
                        printf("\nParty edit complete.\n");
                        break;
                    case 3:
                        printf("\nYou may not edit a candidate's total vote count.\n"
                               "To reverse a single voter's choice enter the 'Edit Voter' menu");
                        break;
                    case 0:
                        //Ensure no lingering inputs are in the buffer
                        fflush(stdin);
                        //Returns to Admin menu
                        break;
                    default:
                        //Input validation
                        printf("\nThat choice was not listed. Please try again.\n");
                        break;
                }
            } while(editChoice != 0);
        }
    }
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);
    printf("\nReturning to Admin Panel...\n");
}