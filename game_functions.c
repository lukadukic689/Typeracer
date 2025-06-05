#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "functions.h"
#include "filetypes.h"

#define SET_CONSOLE_RED SetConsoleTextAttribute(hConsole, 0x4)
#define SET_CONSOLE_GREEN SetConsoleTextAttribute(hConsole, 0x2)
#define SET_CONSOLE_WHITE SetConsoleTextAttribute(hConsole, 0x7)
#define SET_CONSOLE_YELLOW SetConsoleTextAttribute(hConsole, 0x6)
#define IS_A_PRINTABLE_CHAR (letter >= 33 && letter <= 126)



static int incorrect = 0;


//allocating strings, thakes as parameter the ammount of characters the string contains
char* memoryAlloc(int charCount) {
	char* temp = (char*)calloc(charCount, sizeof(char));
	if (!temp) {
		perror("Neuspjesno zauzimanje memorije za text");
		return 1;
	}
	else {
		/*printf("Uspjesno zauzeta memorija za %d chars\n\n", charCount);*/
	}
	return temp;
}


//sta je ovo??
//void readFromKeyboard(int option) {
//	int size = findSize("story1.txt");
//	int i = 0;
//	
//	for (i = 0; i < size; i++) {
//		*(typedText + i) = _getch();
//	}
//}


//displays and reads characters, checks if the entered characters match the text, controls colors via the functions display text N: displays the word thats beeing writen as preview
float cmdControl(const char* const text, char* unsolvedText, char* correctText, char* wrongText, int size, float oldWPM, char* username) { //returns time from end of the countdown till the end of the gamw
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char letter = 5;
	int correct = 0;
	
	int i = 0;
	int timer;
	char* previewText;
	int iPreview = 0;
	char* timerText;
	float wpm = 0;
	int time;
	float fTime;



	typedText = NULL;
	typedText = memoryAlloc(size + 1);

	previewText = NULL;
	previewText = memoryAlloc(26);
	timerText = NULL;
	timerText = memoryAlloc(26);

	timerText = getReady(unsolvedText, correctText, wrongText, previewText, incorrect, timerText);
	
	while (_kbhit()) { //clears buffer of characters which were written while the timer was going on
		_getch();
	}
	timer = 0;
	timer = clock();

		for (int i = 0;; i++) {
			displayText(unsolvedText, correctText, wrongText, previewText, incorrect, timerText);
			if (clock() - timer > 1000)
				emptyString(timerText, 26);
			if ('\0' == *(text + (i)) && incorrect == 0) { // End of the text, leaves the loop
				break;
			}

			letter = _getch();
			if (letter != '\b' && iPreview < 25) {
				*(previewText + iPreview) = letter;
				iPreview++;
			}
			if (letter == 32 && incorrect == 0 && *(text + i) == 32) { //32 = space, if you press space and if the upcoming char in the "story" has a space, the preview text will clear.
				emptyString(previewText, 26);
				iPreview = 0;
			}
			
			if (letter == *(text + (i)) && incorrect <= 0) {
				*(correctText + correct) = letter;
				++correct;
				
			}
			else if (letter == '\b' && i > 0 && *(correctText + (i - 1)) != 32) {
				
				--i;
				--iPreview;
				if (incorrect > 0) {
					incorrect--;
					*(wrongText + incorrect) = NULL;
				}
				if (*(text + (i)) != 32 && incorrect == 0) { //if previous char is space it wont go back and delete the word which was written correctly, it will only allow to delete words which aren't completed.
					--correct;
					*(correctText + correct) = NULL;

				}
				else { //bugfix
					correct--;
				}
				*(previewText + iPreview) = NULL;
				--i;
			}
			else if (IS_A_PRINTABLE_CHAR || letter == 32 && ('\0' != *(text + i))) { //32 = space
				*(wrongText + incorrect) = *(text + i);
				correct++;
				
				//i--;
				incorrect++;
			}
			else {
				i--; //stays at the current letter
			}
			
			unsolvedText = text + i + 1;
	}	
		time = (clock() - timer);
		fTime = time / 1000.0;
		fTime /= 60.0; 

		wpm = (getNumOfWords() / fTime);
		if (oldWPM == 0) {
			printf("\n\n%s.", username);
			printf("\nTvoj WPM (Words Per Minute) iznosi:%.2f", wpm);
			printf("\nKlikni SPACE kako bi nastavio.");
			leaderboardWrite(username, wpm);
		} else if (wpm > oldWPM) {
			SET_CONSOLE_GREEN;
			printf("\n\n%s CESTITKE! NOVI REKORD!!!", username);
			SET_CONSOLE_WHITE;
			printf("\nTvoj WPM (Words Per Minute) iznosi:%.2f", wpm);
			printf("\nKlikni SPACE kako bi nastavio.");
			deleteUser(username);
			leaderboardWrite(username, wpm);
		}
		else if (wpm < oldWPM) {
			printf("\n\n%s", username);
			SET_CONSOLE_RED;
			printf("\nTvoj WPM (Words Per Minute) iznosi:%.2f", wpm);
			printf("\nTvoj rezultat ne rusi tvoj prosli rekord pa se nece biljeziti");
			printf("\nKlikni SPACE kako bi nastavio.");
			SET_CONSOLE_WHITE;
		}
		do {
			letter = _getch();
		} while (letter != 32);

		free(typedText);
		typedText = NULL;
		free(previewText);
		previewText = NULL;
		free(timerText);
		timerText = NULL;

		return(wpm);

		/*return (clock() - timer); */

}


//displays different itterations of texts, changes colors accordingly
void displayText(char* unsolvedText, char* correctText, char* wrongText, char* previewText, int incorrect, char* timerText) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	printf("Napisi sljedeci tekst u sto brzem vremenu: \n\n");
	SET_CONSOLE_GREEN;
	printf("%s", correctText);
	if (incorrect > 0) {
		SET_CONSOLE_RED;
		printf("%s", wrongText);
	}
	SET_CONSOLE_WHITE;
	printf("%s\n\n\n", unsolvedText);

	//preview text:
	
	printf("%s", previewText);

	switch (*(timerText + 0)) {
	case 'C':
		SET_CONSOLE_RED;
		break;
	case 'P':
		SET_CONSOLE_YELLOW;
		break;
	case 'K':
		SET_CONSOLE_GREEN;
		break;
	}

	printf("\n\n\n%s", timerText);
	SET_CONSOLE_WHITE;
	/*printf("%d", );*/
	
}


void emptyString(char* string, int size) {
	if (size <= 0) {
		return;
	}
	*string = '\0';
	emptyString(string + 1, size - 1);

}

char* getReady(char* unsolvedText, char* correctText, char* wrongText, char* previewText, int incorrect, char* timerText) {
	strcpy(timerText, "Cekaj (3)");
	displayText(unsolvedText, correctText, wrongText, previewText, incorrect, timerText);
	Sleep(1000);
	strcpy(timerText, "Priprema (2)");
	displayText(unsolvedText, correctText, wrongText, previewText, incorrect, timerText);
	Sleep(1000);
	strcpy(timerText, "Pozor (1)");
	displayText(unsolvedText, correctText, wrongText, previewText, incorrect, timerText);
	Sleep(1000);
	strcpy(timerText, "Kreni !!!");
	return timerText;
}

float getNumOfWords() {
	
	int numOfSpace = 0;
	int i = 0;

	for (i = 0;; i++) {
		if (*(text + (i)) == 32) {// 32 = space
			numOfSpace++;
		}
		if (*(text + (i)) == '\0') { // End of the text, leaves the loop.
			break;
		}
	}

	return(numOfSpace + 1);
}