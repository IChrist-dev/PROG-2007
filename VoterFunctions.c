#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "StructuresDef.h"
#include "VoterFunctions.h"

//Method to create a unique key code for a voter
char* generateKeyCode() {
    static char allowedKeys[] = "abcdefghijklmnopqrstuvwxyz0123456789";

    //Allocate memory block for new key code. 5 character length is arbitrary
    char *keyCode = malloc(5);

    srand(time(NULL));
    //Assign a random value from the allowedKeys to each position in the key code
    for(int i=0; i<5; i++) {
        int randValue = rand() % (int)(sizeof(allowedKeys) - 1);
        keyCode[i] = allowedKeys[randValue];
    }

    //last position of the string must be empty
    keyCode[5] = '\0';

    return keyCode;
}

//Function to add an officer to the Officer list, one at a time
void addVoters(Voter *voterArray, int votersSize) {
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    printf("\nWelcome to the Voter input page.");
    printf("\n---Voter Input Should Only Be Performed Once---\n");

    for(int i=0; i<votersSize; i++) {
        //Sub-process to exit before optional data input
        printf("\nPress [x] to leave this page. \n"
               "Press [y] to start entering officer information.\n");
        char stayGo;
        scanf(" %c", &stayGo);

        if (stayGo == 'x') {
            //Ensure no lingering inputs are in the buffer
            fflush(stdin);
            break;
        } else if(stayGo == 'y'){

            printf("First Name:");
            scanf("%s", voterArray[i].fName);

            printf("Last Name:");
            scanf("%s", voterArray[i].lName);

            //generate a random keycode for the new voter
            strcpy(voterArray[i].keyCode, generateKeyCode());

            //Initial voting status of a new voter can only be false
            voterArray[i].hasVoted = false;

            //Display new voter output
            printf("New Voter Added with these credentials:\n"
                   "Name: %s %s\n"
                   "Confidential Key Code: %s\n"
                   "\n---Next Voter---\n",
                   voterArray[i].fName,
                   voterArray[i].lName,
                   voterArray[i].keyCode);

            //Add details to a text file for convenience
            FILE *append;

            append = fopen("../Output-Text-Files/AddedVoters.txt", "a");
            fprintf(append, "Name: ");
            fprintf(append, "%s ", voterArray[i].fName);
            fprintf(append, "%s\n", voterArray[i].lName);
            fprintf(append, "Keycode: ");
            fprintf(append, "%s\n\n", voterArray[i].keyCode);

            fclose(append);
        }
    }
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);
}

void editVoters(Voter *voterArray, int votersSize) {
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    printf("\nWelcome to the voter editing page.\n");
    printf("Enter the key code of the voter you'd like to edit:");
    char inputKeyCode[30];
    scanf("%s", &inputKeyCode);

    //Search through Voter array for a key code match
    for (int i = 0; i < votersSize; i++) {
        if (strcmp(inputKeyCode, voterArray[i].keyCode) == 0) {

            int editChoice;
            do {
                //Using bool to print the voted/not voted state of the person
                char tempVoteState;
                if (voterArray[i].hasVoted == true) {
                    tempVoteState = 'Y';
                } else tempVoteState = 'N';

                //Display voter info prior to making changes
                printf("Current Voter Details:\n"
                       "1. Name: %s %s\n"
                       "2. Key Code: %s\n"
                       "3. Has Voted: %c\n"
                       "0. Return to Admin Menu\n"
                       "\nWhich would you like to edit?\n",
                       voterArray[i].fName,
                       voterArray[i].lName,
                       voterArray[i].keyCode,
                       tempVoteState);
                scanf("%d", &editChoice);

                switch (editChoice) {
                    case 1:
                        printf("\nNew First Name:");
                        scanf("%s", voterArray[i].fName);

                        printf("New Last Name:");
                        scanf("%s", voterArray[i].lName);
                        printf("\nName edit complete.\n");
                        break;
                    case 2:
                        //Assign a new random key code
                        strcpy(voterArray[i].keyCode, generateKeyCode());
                        break;
                    case 3:
                        //toggle whether the voter has cast a ballot
                        printf("New Vote status:");
                        voterArray[i].hasVoted = !voterArray[i].hasVoted;
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