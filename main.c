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
    bool hasVoted;
    char candidateChoice[40];
} Voter;

//Functions declaration

void officerLogin(Officer officerArray[], int officersSize);
void addOfficers(Officer *officerArray, int officersSize);
void editOfficers(Officer *officerArray, int officersSize);
char *generateKeyCode();
void addVoters(Voter *voterArray, int votersSize);
void editVoters(Voter *voterArray, int votersSize);
void searchVoters(Voter *voterArray, int votersSize);
void addCandidates(Candidate *candidateArray, int candidatesSize);
int main() {


    Officer officerArray[3];

    //One officer login must exist before starting the program
    Officer adminOfficer = {"rootOfficer", "Admin","root", "123"};
    officerArray[0] = adminOfficer;
    int officersSize = sizeof(officerArray)/sizeof(officerArray[0]);

    printf("Welcome to the Voter Polling Program\n");
    officerLogin(officerArray, officersSize);


    Voter voterArray[5];
    int votersSize = sizeof(voterArray)/sizeof(voterArray[0]);
    Candidate candidateArray[3];
    int candidatesSize = sizeof(candidateArray)/sizeof(candidateArray[0]);

    //region Admin Panel - Main menu and sub-menus
    printf("\n---Admin Panel---\n");
    int masterSwitch = 1;
    do {
        int mainMenuChoice;
        printf("\nMain Menu\n"
               "1. Add Officers\n"
               "2. Edit Officers\n"
               "3. Add Voters\n"
               "4. Edit Voters\n"
               "5. Add Candidates\n"
               "6. Edit Candidates\n"
               "7. Enter Voting Mode\n"
               "0. Shutdown\n");
        scanf("%d", &mainMenuChoice);

        switch(mainMenuChoice) {
            case 1:
                addOfficers(officerArray, officersSize);
                break;

            case 2:
                editOfficers(officerArray, officersSize);
                break;

            case 3:
                addVoters(voterArray, votersSize);
                break;

            case 4:
                editVoters(voterArray, votersSize);
                break;

            case 5:
                addCandidates(candidateArray, candidatesSize);
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

    } while (masterSwitch == 1);
    //endregion

    return 0;
}

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
    Voter tempVoter;

    printf("\nWelcome to the Voter input page.");
    printf("\n---Voter Input---\n");

    for(int i=0; i<votersSize; i++) {
        //Sub-process to exit before optional data input
        printf("Press [x] to leave this page. \n"
               "Press [y] to start entering officer information.\n");
        char stayGo;
        scanf(" %c", &stayGo);

        if (stayGo == 'x') {
            break;
        } else if(stayGo == 'y'){

            printf("First Name:");
            scanf("%s", tempVoter.fName);

            printf("Last Name:");
            scanf("%s", tempVoter.lName);

            //generate a random keycode for the new voter
            strcpy(tempVoter.keyCode, generateKeyCode());

            //Initial voting status of a new voter can only be false
            tempVoter.hasVoted = false;

            voterArray[i] = tempVoter;

            //Display new voter output
            printf("New Voter Added with these credentials:\n"
                   "Name: %s %s\n"
                   "Confidential Key Code: %s\n"
                   "\nNext Voter\n",
                   voterArray[i].fName,
                   voterArray[i].lName,
                   voterArray[i].keyCode);
        }
    }
}

void editVoters(Voter *voterArray, int votersSize) {
    printf("\nWelcome to the voter editing page.\n");
    printf("Enter the key code of the voter you'd like to edit:");
    char inputKeyCode[30];
    scanf("%s", &inputKeyCode);

    for (int i = 0; i < votersSize; i++) {
        if (strcmp(inputKeyCode, voterArray[i].keyCode) == 0) {

            int editChoice;
            do {
                //Using bool to print the voted/not voted state of the person
                char tempVoteState;
                if (voterArray[i].hasVoted == true) {
                    tempVoteState = 'Y';
                } else tempVoteState = 'N';

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
                        break;
                }
            } while (editChoice != 0);
        }
    }
}

//Function to add information to fixed-size Candidate array
void addCandidates(Candidate *candidateArray, int candidatesSize) {
    printf("\nWelcome to the Candidate input page.");

    //Sub-process to exit before optional data input
    printf("\nPress [x] to leave this page.\n"
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