//Abdullah Kidwai
//akidwa2

typedef struct WaitList
{
	char *GroupName;
	int GroupSize;
	int GroupStatus;
	struct WaitList *pNext;
} WaitList;

void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void clearToEoln();
void printCommands();


void doAdd(WaitList *head);
void doCallAhead(WaitList *head);
void doWaiting(WaitList *head);
void doRetrieve(WaitList *head);
void doList(WaitList *head);
void doDisplay(WaitList *head);



int doesNameExist(WaitList *head, char name[]);
void displayListInformation(WaitList *head);
void updateStatus(WaitList *head, char name[]);
int countGroupsAhead(WaitList *head, char name[]);
void displayGroupSizeAhead(WaitList *head, char name[]);
void retrieveAndRemove(WaitList *head, int tableSize);
