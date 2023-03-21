#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Person-type structure definitions
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
    int hasVoted;
    char candidateChoice[40];
} Voter;

//Functions declaration
char *generateKeyCode();
void addOfficer(Officer **officerList, int *officerListSize);
void addVoter(Voter **voterList, int *voterListSize);
void searchVoter(Voter **voterList, int *voterListSize);
void addCandidate(Candidate candidateArray[], int candidateArraySize);

int main() {

    //To simulate booleans, int 0 => false, int 0 => true

    //One officer login must exist before starting the program
    Officer adminOfficer;
    strcpy(adminOfficer.fName, "rootOfficer");
    strcpy(adminOfficer.lName, "n.a.");
    strcpy(adminOfficer.username, "root");
    strcpy(adminOfficer.password, "123");

    int adminUserValid = 0;
    int adminPassValid = 0;

    printf("Welcome to the Voter Polling Program\n"
           "---Admin Login---\n\n"
           "Please enter your login information\n");


    //region Initial Officer Username input
    do {
        char adminUsernameAttempt[30];

        printf("\nAdmin Officer Username:");
        fgets(adminUsernameAttempt, sizeof(adminUsernameAttempt), stdin);

        //Search for \n caused by fgets() and remove it
        //Keeps multiword inputs from accidentally filling the buffer, spoiling the password input
        char *p;
        if ((p = strchr(adminUsernameAttempt, '\n')) != NULL) {
            *p = '\0';
        }


        if (strcmp(adminUsernameAttempt, adminOfficer.username) != 0) {
            printf("We're sorry. That username does not match the Administrator credentials\n");
            continue;
        }
        //If reached, username must be valid
        adminUserValid = 1;


    } while (adminUserValid == 0);
    //endregion

    //region Initial Officer password input
    int badPassAttempts = 0;
    do {
        char adminPasswordAttempt[30];

        printf("\nAdmin Officer Password:");
        scanf("%s", &adminPasswordAttempt);
        if (strcmp(adminPasswordAttempt, adminOfficer.password) != 0) {
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
        adminPassValid = 1;
    } while (adminPassValid == 0);
    //endregion

    //Create addresses of dynamic arrays for each Person-type. Instantiation happens later.
    Officer *officerList = NULL;
    int officerListSize = 0;

    Voter *voterList = NULL;
    int voterListSize = 0;

    Candidate candidateList[3];

    //region Admin Panel - Main menu and sub-menus
    printf("\n---Admin Panel---\n");
    int masterSwitch = 1;
    do {
        int mainMenuChoice;
        printf("\nMain Menu\n"
               "1. Add Officers\n"
               "2. Add Voters\n"
               "3. Search Voters\n"
               "4. Edit Voters\n"
               "5. Add Candidates\n"
               "6. Enter Voting Mode\n"
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
                searchVoter(&voterList, &voterListSize);
                break;

            case 4:
                //edit voters

            case 5:
                addCandidate(candidateList, 3);
                break;

            case 6:
                //enter Voting Mode
                break;

            case 0:
                printf("Have a nice day.\n");
                masterSwitch = 0;
                break;
            default:
                printf("\nThat selection is not recognised. Please try again.\n");
                break;
        }

        //test
        for(int i=0; i<voterListSize; i++) {
            printf("\nName: %s %s\n", voterList[i].fName, voterList[i].lName);
            printf("Key Code: %s\n", voterList[i].keyCode);
            printf("Voted Y/N: %d\n", voterList[i].hasVoted);
        }

    } while (masterSwitch == 1);

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
        printf("Press [x] to leave this page. \n"
               "Press [y] to start entering officer information.\n");
        char stayGo;
        scanf(" %c", &stayGo);

        if (stayGo == 'x') {
            break;
        } else if(stayGo == 'y'){
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

    printf("\nWelcome to the voter input page.");
    do {
        printf("\n---Voter Input---\n");

        //Sub-process to exit before optional data input
        printf("Press [x] to leave this page. \n"
               "Press [y] to start entering officer information.\n");
        char stayGo;
        scanf(" %c", &stayGo);

        if (stayGo == 'x') {
            break;
        } else if(stayGo == 'y'){
            printf("First Name:");
            scanf("%s", &tempVoter.fName);

            printf("Last Name:");
            scanf("%s", &tempVoter.lName);

            //Make a random key
            strcpy(tempVoter.keyCode, generateKeyCode());

            //Display newly added voter info
            printf("---Voter To Add---\n"
                   "Name: %s %s\n"
                   "Key Code: %s\n",
                   tempVoter.fName,
                   tempVoter.lName,
                   tempVoter.keyCode);

            //Voter Array must increase size by 1
            *voterList = realloc(*voterList, (*voterListSize + 1) * sizeof(Voter));

            //Add the tempOfficer to the Officer Array
            strcpy((*voterList)[*voterListSize].fName, tempVoter.fName);
            strcpy((*voterList)[*voterListSize].lName, tempVoter.lName);
            strcpy((*voterList)[*voterListSize].keyCode, generateKeyCode());
            //New voter initially hasn't cast their vote
            (*voterList)[*voterListSize].hasVoted = 0;


            (*voterListSize)++;
        }
    } while (1);
}

//Function to search through the voter list for a specific voter
void searchVoter(Voter **voterList, int *voterListSize) {

    printf("Welcome to the voter search page.\n");

    printf("Please provide a voter keycode:");
    char searchKeyCode[6];
    scanf("%s", &searchKeyCode);

    //Replace the \n caused by pressing the Enter key
    char *p;
    if ((p = strchr(searchKeyCode, '\n')) != NULL) {
        *p = '\0';
    }

    //treating as boolean
    int matchFound = 0;

    printf("%d", *voterListSize);
    for (int i = 0; i <= *voterListSize; i++) {
        if (strcmp(voterList[i]->keyCode, searchKeyCode) == 0) {
            printf("\n***Match found***\n");
            matchFound = 1;
            printf("\nName: %s %s\n", voterList[i]->fName, voterList[i]->lName);
            printf("Key Code: %s\n", voterList[i]->keyCode);
            if (voterList[i]->hasVoted == 1) {
                printf("Has Voted: Yes\n");
            } else {
                printf("Has Voted: No\n");
            }
        }
    }
    if (matchFound == 0) {
        printf("No voter was found using %s", searchKeyCode);
    }


}

//Function to add information to fixed-size Candidate array
void addCandidate(Candidate candidateArray[], int candidateArraySize) {

    printf("\nWelcome to the Candidate input page.");
    printf("\n---Candidate Input---\n");

    //Sub-process to exit before optional data input
    printf("Press [x] to leave this page. \n"
           "Press [y] to start entering candidate information.\n");
    char stayGo;
    scanf(" %c", &stayGo);

    if (stayGo == 'x') {
        return;
    } else if(stayGo == 'y'){
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