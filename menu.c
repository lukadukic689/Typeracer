#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

#include "functions.h"
#include "filetypes.h"

#define SET_CONSOLE_WHITE SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE)
#define YELLOW SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define OPTION_CHOICE_COLOR_G(A,STRING) printf("["); SetConsoleTextAttribute(hConsole, 0x2); printf("%d", A); SetConsoleTextAttribute(hConsole, 0x7); printf("] "); printf("%s", STRING);
#define OPTION_CHOICE_COLOR_B(A,STRING) printf("["); SetConsoleTextAttribute(hConsole, 0x3); printf("%d", A); SetConsoleTextAttribute(hConsole, 0x7); printf("] "); printf("%s\n", STRING);
#define OPTION_EXIT(STRING) printf("["); SetConsoleTextAttribute(hConsole, 0x4); printf("0"); SetConsoleTextAttribute(hConsole, 0x7); printf("] "); printf("%s\n", STRING);


enum options {
	EXIT,
	PLAY,
	CHANGE_TEXT,
	CHANGE_USERNAME,
	LEADERBOARD,
};


void menu(char* path, char* username) {
    int size, fileExists;
    char letter;
    int bool = 0;
    int textOption = -1;
    float wpm;
    char* temp = NULL;
    float oldWPM = 0;
    char* leaderBoardUserName = NULL;
    char* fileToRemove = NULL;
    char* realPathToRemove = NULL;
    realPathToRemove = memoryAlloc(MAX_PATH);
    fileToRemove = memoryAlloc(MAX_PATH);
    temp = memoryAlloc(20);
    leaderBoardUserName = memoryAlloc(20);


    while (1) {
        size = 0;
        system("cls");
        int option = mainOptions(path, username);
        switch (option) {

        case EXIT:
            printf("\n\nIzlaz iz programa.");
            free(temp);
            temp = NULL;
            free(leaderBoardUserName);
            leaderBoardUserName = NULL;
            free(fileToRemove);
            fileToRemove = NULL; 
            return 0;
            break;


        case PLAY:
            system("cls");
            if (bool == 0) { //bugfix
                fileExists = fillArrayWithText(path);
            }
            if (fileExists) {
                bool = 1;
                size = findSize(path);

                unsolvedText = NULL;
                unsolvedText = memoryAlloc(size + 1);
                correctText = NULL;
                correctText = memoryAlloc(size + 1);
                wrongText = NULL;
                wrongText = memoryAlloc(size + 1);

                oldWPM = getWPM(username);


                /*if (oldWPM > 0) {
                    printf("\n\nKORISNIK %s Vec je igro i rekord mu je %f WPM", username, oldWPM);
                    scanf("%i", &size);
                }*/


                strcpy(unsolvedText, text);


                wpm = cmdControl(text, unsolvedText, correctText, wrongText, size + 1, oldWPM, username);

                free(unsolvedText);
                unsolvedText = NULL;
                free(correctText);
                correctText = NULL;
                free(wrongText);
                wrongText = NULL;
            }
            
            break;


        case CHANGE_TEXT:
            system("cls");
            bool = 0;
            textOption = printTextOptions(path); //textOption is an int, means which text is chosen
            if (textOption == EXIT) {
                break;
            }
            else if (textOption == -1) {
                printf("\nUnesi ime datoteke koje zelis izbrisati: ");
                scanf("%s", fileToRemove);
                strcpy(realPathToRemove, "Text\\");
                strcat(realPathToRemove, fileToRemove);
                if (remove(realPathToRemove) != 0) {
                    perror("Greska pri brisanju datoteke");
                } else {
                printf("\nDatoteka \"%s\" je izbrisana!", fileToRemove);
                }
                printf("\nKlikni SPACE kako bi nastavio.");
                do {
                    letter = _getch();
                } while (letter != 32);
            } else {
                //path is already changed but this changes whats written in currentPath.txt
                newCurrentPath(path);
            }
            break;


        case CHANGE_USERNAME: 
            system("cls");
            printf("Unesi novo ime (unesi 0 kako bi odustao): ");
            scanf("%s", temp);

            if (*(temp + 0) == '0') {
                break;
            }
            else {
                strcpy(username, temp);
                newCurrentUser(username);

            }
            break;


        case LEADERBOARD:
            system("cls");
            int LOption = printLeaderboardOptions();
            if (LOption == EXIT) {
                break;
            }
            switch (LOption) {
            case 1:
                printLeaderboard();
                break;
            case 2:
                printf("\nUnesi ime igraca kojeg zelis izbrisati: ");
                scanf("%s", leaderBoardUserName);
                deleteUser(leaderBoardUserName);
                printf("\nKorisnik %s je izbrisan!", leaderBoardUserName);
                break;
            case 3:
                printSearch();
                break;
            }
        }
    }
}