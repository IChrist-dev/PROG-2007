#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StructuresDef.h"
#include "OfficerFunctions.h"

//Function for validating officer login
int officerLogin(Officer *officerArray, int officersSize) {
    //region Initial Officer Username input
    printf("---Admin Login---\n\n"
           "Please enter your login information\n");
    do {
        char adminUsernameAttempt[30];

        printf("\nOfficer Username:");
        fgets(adminUsernameAttempt, sizeof(adminUsernameAttempt), stdin);

        //Search for \n caused by fgets() and remove it
        //Keeps multiword inputs from accidentally filling the buffer, spoiling the password input
        char *p;
        if ((p = strchr(adminUsernameAttempt, '\n')) != NULL) {
            *p = '\0';
        }

        for (int i = 0; i < officersSize; i++) {
            if (strcmp(adminUsernameAttempt, officerArray[i].username) == 0) {

                //region Root Officer password input
                int badPassAttempts = 0;
                do {
                    char adminPasswordAttempt[30];

                    printf("\nOfficer Password:");
                    scanf("%s", &adminPasswordAttempt);

                    if (strcmp(adminPasswordAttempt, officerArray[i].password) == 0) {
                        //Ensure no lingering inputs are in the buffer
                        fflush(stdin);

                        //returns 0 if login is successful
                        return 0;
                    }


                    printf("We're sorry. That password does not match any officer credentials\n");
                    badPassAttempts++;

                    //Return 1 means too many unsuccessful logins
                    if (badPassAttempts >= 3) {
                        //Ensure no lingering inputs are in the buffer
                        fflush(stdin);
                        return 1;
                    }
                } while (1);
                //endregion
            }
        }
        printf("We're sorry. That username doesn't match any listed polling officer.\n");
    } while (1);
}

//Function to add an officer to the Officer list, one at a time
void addOfficers(Officer *officerArray, int officersSize) {
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    printf("\nWelcome to the officer input page.");
    printf("\n---Officer Input Should Only Be Performed Once---\n");

    for(int i=1; i<officersSize; i++) {
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
            scanf("%s", officerArray[i].fName);

            printf("Last Name:");
            scanf("%s", officerArray[i].lName);

            printf("Username:");
            scanf("%s", officerArray[i].username);

            printf("Password:");
            scanf("%s", officerArray[i].password);

            printf("Officer details added.\n");
        }
    }
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);
    printf("\nReturning to Admin Panel...\n");
}

void editOfficers(Officer *officerArray, int officersSize) {
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    printf("\nWelcome to the officer editing page.\n");
    printf("Enter the username of the officer you'd like to edit:");
    char inputOfficerUName[30];

    scanf("%s", &inputOfficerUName);

    for(int i=0; i<officersSize; i++) {
        if(strcmp(inputOfficerUName, officerArray[i].username) == 0) {
            printf("Password:");
            char inputOfficerPWord[30];
            scanf("%s", &inputOfficerPWord);

            if(strcmp(inputOfficerPWord, officerArray[i].password) == 0) {
                printf("Password Correct.\n");

                int editChoice;
                do {
                    printf("Current Officer Details:\n"
                           "1. Name: %s %s\n"
                           "2. Username: %s\n"
                           "3. Password: %s\n"
                           "0. Return to Admin Menu\n"
                           "\nWhich would you like to edit?\n",
                           officerArray[i].fName,
                           officerArray[i].lName,
                           officerArray[i].username,
                           officerArray[i].password);
                    scanf("%d", &editChoice);

                    switch (editChoice) {
                        case 1:
                            printf("\nNew First Name:");
                            scanf("%s", officerArray[i].fName);

                            printf("New Last Name:");
                            scanf("%s", officerArray[i].lName);
                            printf("\nName edit complete.\n");
                            break;
                        case 2:
                            printf("\nNew Username:");
                            scanf("%s", officerArray[i].username);
                            break;
                        case 3:
                            printf("New Password:");
                            scanf("%s", officerArray[i].password);
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
    }
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);
    printf("\nReturning to Admin Panel...\n");
}

//Function for officers to view the voting statistics for all candidates
void reviewStats(Candidate *candidateArray, int candidatesSize) {
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    printf("\nWelcome to the Statistics Review Page\n"
           "#\tName\t\tParty\t\tVote Count");
    for(int i=0; i<candidatesSize; i++) {
        printf("\n%d.\t%s %s\t%s\t\t%d\n",
               i+1,
               candidateArray[i].fName,
               candidateArray[i].lName,
               candidateArray[i].party,
               candidateArray[i].voteCount);
    }

    printf("\nWould you like to declare the winner? Y/N\n");
    char declareWin;
    scanf("%c", &declareWin);

    if(declareWin == 'Y' || declareWin == 'y') {
        int indexOfWinner;
        int highestVoteCount = 0;

        //Compare all the voteCounts to find the highest one and save that candidate's array index
        for(int i=0; i<candidatesSize; i++) {
            if(candidateArray[i].voteCount > highestVoteCount) {
                highestVoteCount = candidateArray[i].voteCount;
                indexOfWinner = i;
            }
        }

        if(highestVoteCount != 0) {
            //Display the winner
            printf("\nElection Winner: %s %s\n"
                   "Party: %s\n"
                   "Vote Count: %d\n"
                   "\nDo you wish to close the program now? Y/N\n",
                   candidateArray[indexOfWinner].fName,
                   candidateArray[indexOfWinner].lName,
                   candidateArray[indexOfWinner].party,
                   candidateArray[indexOfWinner].voteCount);
        } else {
            printf("\nNo winner can be declared\n"
                   "All vote counts are zero.\n");

            //Ensure no lingering inputs are in the buffer
            fflush(stdin);
        }

        //Ensure no lingering inputs are in the buffer
        fflush(stdin);

        char shutdownYN;
        scanf("%c", &shutdownYN);

        if(shutdownYN == 'Y' || shutdownYN == 'y') {
            printf("\nProgram now closing. Bye\n");
            exit(0);
        }
    }
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);
    printf("\nReturning to Admin Panel...\n");
}