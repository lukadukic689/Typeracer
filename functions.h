#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int fillArrayWithText(const char* path);
long int findSize(const char* path);
void newCurrentPath(const char* path);
void newCurrentUser(const char* username);
float getWPM(const char* username);
void deleteUser(const char* username);

void printColoredText(const char*);
char* memoryAlloc(int);

void displayText(const char* unsolvedText, const char* correctText, const char* wrongText, const char* previewText, int incorrect, const char* );
float cmdControl(char* text, char* unslovedText, char* correctText, char* wrongText, int size, float oldWPM, char* username); //returns WPM
void emptyString(char* string, int size);
char* getReady(char* unsolvedText, char* correctText, char* wrongText, char* previewText, int incorrect, char* timerText);
void menu(char* path, char* username);
int mainOptions(char* path, char* username);
int printTextOptions(char*);

int printLeaderboardOptions(void);
void printLeaderboard(void);
//void playerCount(void);
void leaderboardWrite(/*int countOfUser, */char* username, double wpm);
float getNumOfWords();
float getNumOfUsersInLeaderBoard();

void printLeaderboard(void);
int countUsers(void);
int compareUsers(const void* a, const void* b);
void printSearch(void);
void getLimitedString(char* string, int limit);


#endif //FUNCTIONS_H