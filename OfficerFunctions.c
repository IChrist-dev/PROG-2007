#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StructuresDef.h"
#include "OfficerFunctions.h"

//Function for validating officer login
void officerLogin(Officer officerArray[], int officersSize) {
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
                        adminPassValid = true;
                        return;
                    }


                    printf("We're sorry. That password does not match any officer credentials\n");
                    badPassAttempts++;

                    //Shut the program down if too many bad passwords are entered
                    if (badPassAttempts >= 5) {
                        printf("You've made too many failed attempts. The system will now shutdown.\n"
                               "Goodbye...\n");
                        exit(0);
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
    Officer tempOfficer;

    printf("\nWelcome to the officer input page.");
    printf("\n---Officer Input---\n");

    for(int i=1; i<officersSize; i++) {
        //Sub-process to exit before optional data input
        printf("Press [x] to leave this page. \n"
               "Press [y] to start entering officer information.\n");
        char stayGo;
        scanf(" %c", &stayGo);

        if (stayGo == 'x') {
            break;
        } else if(stayGo == 'y'){

            printf("First Name:");
            scanf("%s", tempOfficer.fName);

            printf("Last Name:");
            scanf("%s", tempOfficer.lName);

            printf("Username:");
            scanf("%s", tempOfficer.username);

            printf("Password:");
            scanf("%s", tempOfficer.password);

            officerArray[i] = tempOfficer;

            printf("Officer details added.\n");
        }
    }
}

void editOfficers(Officer *officerArray, int officersSize) {
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
                            break;
                    }
                } while(editChoice != 0);
            }
        }
    }
}