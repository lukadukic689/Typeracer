#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void fillArrayWithText(char*);
void printColoredText(const char*);
char* memoryAlloc(int);
long int findSize(const char* path);
//void readFromKeyboard(int);
void displayText(char* unsolvedText, char* correctText, char* wrongText, char* previewText, int incorrect, char* );
float cmdControl(char* text, char* unslovedText, char* correctText, char* wrongText, int size, float oldWPM, char* username); //returns WPM
void emptyString(char* string, int size);
char* getReady(char* unsolvedText, char* correctText, char* wrongText, char* previewText, int incorrect, char* timerText);
void menu(char* path, char* username);
int mainOptions(char* path, char* username);
int printTextOptions(char*);
void newCurrentPath(char*);
void newCurrentUser(char*);
int printLeaderboardOptions(void);
void printLeaderboard(void);
//void playerCount(void);
void leaderboardWrite(/*int countOfUser, */char* username, double wpm);
float getNumOfWords();
float getNumOfUsersInLeaderBoard();
float getWPM(char* username); //returns Best WPM
//float getBestWPM(char* username);
void deleteUser(char* username);
void printLeaderboard(void);
int countUsers(void);
int compareUsers(const void* a, const void* b);
void printSearch(void);

#endif //FUNCTIONS_H