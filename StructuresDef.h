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
