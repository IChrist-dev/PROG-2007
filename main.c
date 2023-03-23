#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "StructuresDef.h"
#include "OfficerFunctions.h"
#include "VoterFunctions.h"
#include "CandidateFunctions.h"
#include "VoterPanel.h"

int main() {

    //One officer login must exist before starting the program
    Officer adminOfficer = {"rootOfficer", "Admin","root", "123"};

    //There can be a maximum of 3 officers at a voting site
    Officer officerArray[3];
    officerArray[0] = adminOfficer;
    int officersSize = sizeof(officerArray)/sizeof(officerArray[0]);

    printf("Welcome to the Voter Polling Program\n");
    int initialLogin = officerLogin(officerArray, officersSize);
    if(initialLogin != 0) {
        printf("You've made too many failed attempts. The system will now shutdown.\n"
               "Goodbye...\n");
        return 0;
    }


    //Create the voter and candidate arrays for later usage
    Voter voterArray[5];
    int votersSize = sizeof(voterArray)/sizeof(voterArray[0]);

    Candidate candidateArray[3];
    int candidatesSize = sizeof(candidateArray)/sizeof(candidateArray[0]);
    //Ensure no lingering inputs are in the buffer
    fflush(stdin);

    //region Admin Panel - Main menu and sub-menus
    printf("\n---Admin Panel---\n");
    char input[256];
    int mainMenuChoice;
    bool masterSwitch = false;
    do {
        printf("\nMenu\n"
               "1. Add Officers\n"
               "2. Edit Officers\n"
               "3. Add Voters\n"
               "4. Edit Voters\n"
               "5. Add Candidates\n"
               "6. Edit Candidates\n"
               "7. Enter Voting Mode\n"
               "8. Review Statistics\n"
               "9. Shutdown\n");
        fgets(input, sizeof(input), stdin);
        mainMenuChoice = strtol(input, NULL, 10);
        //Ensure no lingering inputs are in the buffer
        fflush(stdin);

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
                editCandidates(candidateArray, candidatesSize);
                break;

            case 7:
                enterVoterPanel(officerArray, officersSize, voterArray, votersSize, candidateArray, candidatesSize);
                break;

            case 9:
                printf("Have a nice day.\n");
                return 0;

            default:
                //Input validation
                printf("\nThat input is not recognized. Please try again.\n");
                break;
        }
    } while (mainMenuChoice != 9);
    //endregion

    return 0;
}