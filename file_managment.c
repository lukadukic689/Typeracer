#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "functions.h"
#include "filetypes.h"



//function which reads a .txt file, and what it contains is assigned to a string
int fillArrayWithText(char* path) { //returns if its possible to read a file (prevents crashes)
	FILE* fp;
	char letter;
	int i = 0;
	char* realPath = NULL;
	realPath = memoryAlloc(MAX_PATH);
	strcpy(realPath, "Text\\");
	strcat(realPath, path);

	printf("\n\n\n%s\n", realPath);
	strcpy(path, realPath);


	i = 0;

	long int size = findSize(realPath);
	if (size == 0) {
		return 0;
	}

	text = NULL;
	text = memoryAlloc(size + 1);

	fp = fopen(realPath, "r");
	if (fp == NULL) {
		printf("Datoteka se ne moze otvoriti.\n");
	}
	else {
		i = 0;
		while (fscanf(fp, "%c", &letter) != EOF) {
			*(text + i) = letter;
			i++;
		}
	}




	printf("\n\n");
	fclose(fp);
	free(realPath);
	realPath = NULL;
	return 1;
}


//currentPath.txt gets updated so every time the program is launched the last picked text will be selected as default
void newCurrentPath(char* path) {
	FILE* fp;
	fp = fopen("currentPath.txt", "w");


	fprintf(fp, "%s", path);
	fclose(fp);

	return 0;
}


//function returns the size of bytes of a file (path) when called
long int findSize(char* path) {
	char letter;
	FILE* fp = fopen(path, "r");

	if (fp == NULL) {
		printf("Tekst nije pronaden! Molim te izaberi neki od dostupnih tekstova u meniju.\n");
		printf("\nPritisni SPACE za nastavak.");
		do {
			letter = _getch();
		} while (letter != 32);

		return 0;
	}

	fseek(fp, 0L, SEEK_END);
	long int res = ftell(fp);

	fclose(fp);

	return res;
}

void newCurrentUser(char* username) {
	FILE* fp;
	fp = fopen("currentUser.txt", "w");


	fprintf(fp, "%s", username);
	fclose(fp);

	return 0;
}

//int playerCount(void) {
//	FILE* fp;
//	fp = fopen("userLeaderboard.txt", "r");
//	char letter;
//
//	if (fp == NULL) {
//		printf("File Not Found!\n");
//		return -1;
//	}
//	else {
//		int i = 0;
//		while (fscanf(fp, "%c", &letter) != EOF) {
//			if (letter == ';') { //; seperator in the userLeaderboard.txt seperates users
//				i++;
//			}
//		}
//	}
//	return 0;
//}

void leaderboardWrite(/*int countOfUser, */char* username, double wpm) {
	FILE* fp = fopen("userLeaderboard.txt", "a");

	fprintf(fp, "%s,%lf;", username, wpm);

	fclose(fp);
}

float getWPM(char* username) { //retursn wpm
	FILE* fp = fopen("userLeaderboard.txt", "r");
	float wpm = 0.0;
	int i = 0;
	char letter;
	char* foundUser = NULL;

	foundUser = memoryAlloc(20);

	if (fp == NULL) {
		printf("File Not Found!\n");
		return 0;
	}
	while (fscanf(fp, "%c", &letter) != EOF) {
		if (letter == ',') {
			if ((strcmp(foundUser, username)) == 0) {
				fscanf(fp, "%f", &wpm);


			}
			while (fscanf(fp, "%c", &letter)) {
				if (letter == ';') {
					emptyString(foundUser, 20);
					fscanf(fp, "%c", &letter);
					i = 0;
					break;
				}
			}
		}
		
		*(foundUser + i) = letter;
		i++;
		
	}

	fclose(fp);
	free(foundUser);
	foundUser = NULL;
	return wpm;
}

void deleteUser(char* username) {
	FILE* fp = fopen("userLeaderboard.txt", "r");
	char* tempString = NULL;
	int i = 0;
	int k = 0;
	int begin = 0;
	int end = 0;
	int difference = 0;
	char letter;
	
	char* foundUser = NULL;

	tempString = memoryAlloc(findSize("userLeaderboard.txt") + 1); //alloc string for the leaderboard info

	foundUser = memoryAlloc(20);

	if (fp == NULL) {
		printf("File Not Found!\n");
		return 0;
	}
	while (fscanf(fp, "%c", &letter) != EOF) {
		k++;
		if (letter == ',') {
			if ((strcmp(foundUser, username)) == 0) {
				begin = k - strlen(username) -1;
				while (fscanf(fp, "%c", &letter)) {
					k++;
					if (letter == ';') {
						emptyString(foundUser, 20);
						fscanf(fp, "%c", &letter);
						k++;
						break;
						
					}
					i++;
				}
				end = k - 2;


			}
			while (fscanf(fp, "%c", &letter)) {
				k++;
				if (letter == ';') {
					emptyString(foundUser, 20);
					fscanf(fp, "%c", &letter);
					k++;
					i = 0;
					break;
				}
			}
		}

		*(foundUser + i) = letter;
		i++;

	}
	fclose(fp);
	
	difference = end - begin;
	
	fp = fopen("userLeaderboard.txt", "r");
	i = 0;
	int j = 0;
	int size = findSize("userLeaderboard.txt");
	for (int k = 0; k < size; k++) {
		fscanf(fp, "%c", &letter);
		if (i == begin) {
			while (j < difference + 1 && fscanf(fp, "%c", &letter) != EOF) {
				k++;
				j++;
			}
			if (letter == ';') { //BUGFIX
				letter = '\0';
			}
			
		}
		*(tempString + i) = letter;
		i++;
	}
	

	fclose(fp);

	fp = fopen("userLeaderboard.txt", "w");
	fprintf(fp, "%s", tempString);
	fclose(fp);
	free(tempString);
	tempString = NULL;
	free(foundUser);
	foundUser = NULL;
}

//float getBestWPM(char* username) {
//	FILE* fp = fopen("userLeaderboard.txt", "r");
//	int res = 0;
//	int i = 0;
//	char letter;
//
//	if (fp == NULL) {
//		printf("File Not Found!\n");
//		return 0;
//	}
//	while (fscanf(fp, "%c", &letter) != EOF) {
//		if (letter == ',') {
//			while (fscanf(fp, "%c", &letter)) {
//				if (letter == ';') {
//					fscanf(fp, "%c", &letter);
//					i = 0;
//					break;
//				}
//			}
//		}
//
//		*(foundUser + i) = letter;
//		i++;
//		if ((strcmp(foundUser, username)) == 0) {
//			res = 1;
//		}
//	}
//
//	fclose(fp);
//	return res;
//}

int countUsers(void) {
	FILE* fp = fopen("userLeaderboard.txt", "r");
	if (!fp) return 0;

	int count = 0;
	char ch;
	while (fscanf(fp, "%c", &ch) != EOF) {
		if (ch == ';') count++;
	}

	fclose(fp);
	return count;
}
