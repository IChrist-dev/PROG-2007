#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Person-type structure definitions
typedef struct {
    char username[30];
    char password[30];
} Admin;

typedef struct {
    char fName[20];
    char lName[20];
    char username[30];
    char password[30];
} Officer;

typedef struct {
    char fName[20];
    char lName[20];
    char party[20];
    int voteCount;
} Candidate;

typedef struct {
    char fName[20];
    char lName[20];
    char keyCode[6];
    bool hasVoted;
    char candidateChoice[40];
} Voter;

//Functions declaration
char *generateKeyCode();
void addOfficer(Officer **officerList, int *officerListSize);
void addVoter(Voter **voterList, int *voterListSize);
void addCandidate(Candidate candidateArray[], int candidateArraySize);

int main() {

    //Only one admin for whole program
    Admin administrator;
    strcpy(administrator.username, "root");
    strcpy(administrator.password, "123");

    bool adminUserValid = false;
    bool adminPassValid = false;

    printf("Welcome to the Voter Polling Program\n"
           "---Admin Login---\n\n"
           "Please enter your login information\n");


    //region Admin Username input
    do {
        char adminUsernameAttempt[30];

        printf("\nAdmin Username:");
        fgets(adminUsernameAttempt, sizeof(adminUsernameAttempt), stdin);

        //Search for \n caused by fgets() and remove it
        //Keeps multiword inputs from accidentally filling the buffer, spoiling the password input
        char *p;
        if ((p = strchr(adminUsernameAttempt, '\n')) != NULL)
            *p = '\0';


        if (strcmp(adminUsernameAttempt, administrator.username) != 0) {
            printf("We're sorry. That username does not match the Administrator credentials\n");
            continue;
        }
        //If reached, username must be valid
        adminUserValid = true;


    } while (!adminUserValid);
    //endregion

    //region Admin password input
    int badPassAttempts = 0;
    do {
        char adminPasswordAttempt[30];

        printf("\nAdmin Password:");
        scanf("%s", &adminPasswordAttempt);
        if (strcmp(adminPasswordAttempt, administrator.password) != 0) {
            printf("We're sorry. That password does not match the Administrator credentials\n");
            badPassAttempts++;

            //Shut the program down if too many bad passwords are entered
            if (badPassAttempts >= 3) {
                printf("You've made too many failed attempts. The system will now shutdown.\n"
                       "Goodbye...\n");
                return 0;
            }
            continue;
        }
        //if reached, password must be valid
        adminPassValid = true;
    } while (!adminPassValid);
    //endregion

    //Create addresses of dynamic arrays for each Person-type. Instantiation happens later.
    Officer *officerList = NULL;
    int officerListSize = 0;

    Voter *voterList = NULL;
    int voterListSize = 0;

    Candidate candidateList[3];

    //region Admin Panel - Main menu and sub-menus
    printf("\n---Admin Panel---\n");
    bool masterSwitch = true;
    int mainMenuChoice;
    do {
        printf("\nMain Menu\n"
               "1. Add Officers\n"
               "2. Add Voters\n"
               "3. Add Candidates\n"
               "4. Enter Voting Mode\n"
               "0. Shutdown\n");
        scanf("%d", &mainMenuChoice);

        switch(mainMenuChoice) {
            case 1:
                addOfficer(&officerList, &officerListSize);
                break;

            case 2:
                addVoter(&voterList, &voterListSize);
                break;

            case 3:
                addCandidate(candidateList, 3);
                break;

            case 4:
                //enter Voting Mode
                break;
            case 0:
                printf("Have a nice day.\n");
                masterSwitch = false;
                break;
            default:
                printf("\nThat selection is not recognised. Please try again.\n");
                break;
        }
    } while (masterSwitch);

    free(officerList);
    free(voterList);
    //endregion
    return 0;
}

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
void addOfficer(Officer **officerList, int *officerListSize) {
    Officer tempOfficer;

    printf("\nWelcome to the officer input page.");
    do {
        printf("\n---Officer Input---\n");

        //Sub-process to exit before optional data input
        printf("Press x to leave this page. \n"
               "Press any other button to start entering officer information.\n");
        char stayGo;
        scanf(" %c", &stayGo);

        if (stayGo == 'x') {
            break;
        } else {
            printf("First Name:");
            scanf("%s", &tempOfficer.fName);

            printf("Last Name:");
            scanf("%s", &tempOfficer.lName);

            printf("Username:");
            scanf("%s", &tempOfficer.username);

            printf("Password:");
            scanf("%s", &tempOfficer.password);

            //Officer Array must increase size by 1
            *officerList = realloc(*officerList, (*officerListSize + 1) * sizeof(Officer));

            //Add the tempOfficer to the Officer Array
            strcpy((*officerList)[*officerListSize].fName, tempOfficer.fName);
            strcpy((*officerList)[*officerListSize].lName, tempOfficer.lName);
            strcpy((*officerList)[*officerListSize].username, tempOfficer.username);
            strcpy((*officerList)[*officerListSize].password, tempOfficer.password);

            (*officerListSize)++;
        }
    } while (1);
}

//Function to add an officer to the Officer list, one at a time
void addVoter(Voter **voterList, int *voterListSize) {
    Voter tempVoter;

    printf("\nWelcome to the officer input page.");
    do {
        printf("\n---Officer Input---\n");

        //Sub-process to exit before optional data input
        printf("Press x to leave this page. \n"
               "Press any other button to start entering officer information.\n");
        char stayGo;
        scanf(" %c", &stayGo);

        if (stayGo == 'x') {
            break;
        } else {
            printf("First Name:");
            scanf("%s", &tempVoter.fName);

            printf("Last Name:");
            scanf("%s", &tempVoter.lName);

            //New voter initially hasn't voted
            tempVoter.hasVoted = false;

            //Voter Array must increase size by 1
            *voterList = realloc(*voterList, (*voterListSize + 1) * sizeof(Officer));

            //Add the tempOfficer to the Officer Array
            strcpy((*voterList)[*voterListSize].fName, tempVoter.fName);
            strcpy((*voterList)[*voterListSize].lName, tempVoter.lName);
            strcpy((*voterList)[*voterListSize].keyCode, generateKeyCode());

            (*voterListSize)++;
        }
    } while (1);
}

//Function to add information to fixed-size Candidate array
void addCandidate(Candidate candidateArray[], int candidateArraySize) {

    printf("\nWelcome to the Candidate input page.");
    printf("\n---Candidate Input---\n");

    //Sub-process to exit before optional data input
    printf("Press x to leave this page. \n"
           "Press any other button to start entering candidate information.\n");
    char stayGo;
    scanf(" %c", &stayGo);

    if (stayGo == 'x') {
        return;
    } else {
        for (int i = 0; i < 3; i++) {
            printf("\n---Candidate %d---", (i + 1));

            printf("\nFirst name:");
            scanf("%s", candidateArray[i].fName);

            printf("Last name:");
            scanf("%s", candidateArray[i].lName);

            printf("Party:");
            scanf("%s", candidateArray[i].party);
            printf("\nCandidate %d has been added.\n", (i + 1));
        }
    }
}