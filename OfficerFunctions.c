#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StructuresDef.h"
#include "OfficerFunctions.h"

//Function for validating officer login
int officerLogin(Officer *officerArray, int officersSize) {
    //region Initial Officer Username input
    bool adminUNameValid = false;
    bool adminPassValid = false;
    printf("---Admin Login---\n\n"
           "Please enter your login information\n");
    do {
        char adminUsernameAttempt[30];

        printf("\nRoot Officer Username:");
        fgets(adminUsernameAttempt, sizeof(adminUsernameAttempt), stdin);

        //Search for \n caused by fgets() and remove it
        //Keeps multiword inputs from accidentally filling the buffer, spoiling the password input
        char *p;
        if ((p = strchr(adminUsernameAttempt, '\n')) != NULL) {
            *p = '\0';
        }

        for (int i = 0; i < officersSize; i++) {
            if (strcmp(adminUsernameAttempt, officerArray[i].username) == 0) {
                adminUNameValid = true;

                //region Root Officer password input
                int badPassAttempts = 0;
                do {
                    char adminPasswordAttempt[30];

                    printf("\nRoot Officer Password:");
                    scanf("%s", &adminPasswordAttempt);

                    if (strcmp(adminPasswordAttempt, officerArray[i].password) == 0) {
                        //Ensure no lingering inputs are in the buffer
                        fflush(stdin);

                        adminPassValid = true;
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