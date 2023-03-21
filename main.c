#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StructuresDef.h"
#include "OfficerFunctions.h"
#include "VoterFunctions.h"

//Functions declaration

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