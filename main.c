#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "StructuresDef.h"
#include "OfficerFunctions.h"
#include "VoterFunctions.h"
#include "CandidateFunctions.h"
#include "VoterPanel.h"

int main() {

    //Erase any text files create during a previous run of the program
    FILE *fOfficerPtr, *fCandidatePtr, *fVoterPtr;
    fOfficerPtr = fopen("../Output-Text-Files/AddedOfficers.txt", "w");
    fclose(fOfficerPtr);

    fCandidatePtr = fopen("../Output-Text-Files/AddedCandidates.txt", "w");
    fclose(fCandidatePtr);

    fVoterPtr = fopen("../Output-Text-Files/AddedVoters.txt", "w");
    fclose(fVoterPtr);

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
    Voter voterArray[10];
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
               "3. Add Candidates\n"
               "4. Edit Candidates\n"
               "5. Add Voters\n"
               "6. Edit Voters\n"
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
                addCandidates(candidateArray, candidatesSize);
                break;

            case 4:
                editCandidates(candidateArray, candidatesSize);
                break;

            case 5:
                addVoters(voterArray, votersSize);
                break;

            case 6:
                editVoters(voterArray, votersSize);
                break;

            case 7:
                enterVoterPanel(officerArray, officersSize, voterArray, votersSize, candidateArray, candidatesSize);
                break;

            case 8:
                reviewStats(candidateArray, candidatesSize);
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
}

