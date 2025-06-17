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



int mainOptions(char* path, char* username) {
    int option;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("--------------------------------------------------------------\n");
    OPTION_CHOICE_COLOR_G(1, "Igraj\n");
    OPTION_CHOICE_COLOR_G(2, "Promejni tekst (trenutno odabrani tekst: "); printf("%s)\n", path);
    OPTION_CHOICE_COLOR_G(3, "Promjeni ime (trenutni igrac: "); printf("%s)\n", username);
    OPTION_CHOICE_COLOR_G(4, "Ljestvica Igraca\n");
    OPTION_EXIT("Izlaz");
    printf("--------------------------------------------------------------\n");
    while (1) {
        printf("Unesi opciju: ");
        if (scanf("%d", &option) != 1) {
            printf("Pogresan unos, pokusaj ponovo.\n");
            while (getchar() != '\n'); // clear the input buffer
            continue;
        }
        if (option < 0 || option > 4) {
            printf("Pogresan unos, pokusaj ponovo.\n");
            continue;
        }
        break;
    }
    return option;
}

int printTextOptions(char* path) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    char searchPath[MAX_PATH];
    int i = 1;
    int option;

    snprintf(searchPath, MAX_PATH, "text\\*");

    hFind = FindFirstFileA(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening directory: %lu\n", GetLastError());
        return;
    }
    printf("--------------------------------------------------------------\n");
    do {
        if (strcmp(findData.cFileName, ".") == 0 ||
            strcmp(findData.cFileName, "..") == 0) {
            continue;
        }
        OPTION_CHOICE_COLOR_G(i, findData.cFileName);
        printf("\n");
        i++;
    } while (FindNextFileA(hFind, &findData) != 0);
    OPTION_CHOICE_COLOR_B(i, "Izbrisi tekst"); //remove()
    OPTION_EXIT("Natrag");
    printf("--------------------------------------------------------------\n");

    DWORD error = GetLastError();
    if (error != ERROR_NO_MORE_FILES) {
        printf("Error during search: %lu\n", error);
    }
    FindClose(hFind);

    //read input
    while (1) {
        printf("Unesi opciju: ");
        if (scanf("%d", &option) != 1) {
            printf("Pogresan unos, pokusaj ponovo.\n");
            while (getchar() != '\n'); // clear the input buffer
            continue;
        }
        if (option == i) {
            return -1;
        }
        if (option < 0 || option > i) {
            printf("Pogresan unos, pokusaj ponovo.\n");
            continue;
        }
        break;
    }
    i = 0;
    snprintf(searchPath, MAX_PATH, "text\\*");

    hFind = FindFirstFileA(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening directory: %lu\n", GetLastError());
        return;
    }
    do {
        if (strcmp(findData.cFileName, ".") == 0 ||
            strcmp(findData.cFileName, "..") == 0) {
            continue;
        }
        strcpy(path, findData.cFileName);
        i++;
    } while (FindNextFileA(hFind, &findData) != 0 && i != option); //the path of the number which was picked get copied to the pointer "path"


    FindClose(hFind);
    return option;
}

int printLeaderboardOptions(void) {
    int option;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    printf("--------------------------------------------------------------\n");
    OPTION_CHOICE_COLOR_G(1, "Prikaz ljestvice\n"); //read
    OPTION_CHOICE_COLOR_G(2, "Brisanje igraca\n"); //delete
    OPTION_CHOICE_COLOR_G(3, "Pretraga igraca\n");
    //update je ako postojeci korsinik napravi novo najbolje vrijeme.
    //insert je umecenje novog ili postojeceg igraca u ljestivcu ovisno o tome kako je igrao
    //create slicno ko i insert , novi igraci se dodaju u ljestvicu i rangirani su ovisno o tome kako su dobro odigrali.
    OPTION_EXIT("Izlaz");
    printf("--------------------------------------------------------------\n");
    while (1) {
        printf("Unesi opciju: ");
        if (scanf("%d", &option) != 1) {
            printf("Pogresan unos, pokusaj ponovo.\n");
            while (getchar() != '\n'); // clear the input buffer
            continue;
        }
        if (option < 0 || option > 3) {
            printf("Pogresan unos, pokusaj ponovo.\n");
            continue;
        }
        break;
    }
    return option;
}


void printLeaderboard(void) {
    char letter;
    int numUsers = countUsers();
    USER* users = malloc(sizeof(USER) * numUsers);

    FILE* fp = fopen("userLeaderboard.txt", "r");
    for (int i = 0; i < numUsers; i++) {
        (*(users + i)).username = malloc(21);  // allocate for username
        fscanf(fp, "%[^,],%f;", (*(users + i)).username, &((*(users + i)).bestWPM));
    }

    fclose(fp);
    
    qsort(users, numUsers, sizeof(USER), compareUsers); //qsort

    for (int i = 0; i < numUsers; i++) {
        printf("%d.%s  | WPM: %f\n",i + 1, (*(users + i)).username, (*(users + i)).bestWPM);
    }

    for (int i = 0; i < numUsers; i++) {
        free((*(users + i)).username);
    }
    free(users);
    users = NULL;

    printf("\nKlikni SPACE kako bi nastavio.");

    do {
        letter = _getch();
    } while (letter != 32);
}

int compareUsers(const void* a, const void* b) {
    const USER* userA = (const USER*)a;
    const USER* userB = (const USER*)b;

    if (userB->bestWPM > userA->bestWPM) return 1;
    if (userB->bestWPM < userA->bestWPM) return -1;
    return 0;
}

int compareUsersByName(const void* a, const void* b) {
    const USER* userA = (const USER*)a;
    const USER* userB = (const USER*)b;
    return strcmp(userA->username, userB->username);
}

void printSearch() {
    system("cls");
    printf("Unesi ime korisinika kojeg zelis pretraziti: ");

    char searchName[21];
    scanf("%20s", searchName);

    char letter;
    int numUsers = countUsers();
    USER* users = malloc(sizeof(USER) * numUsers);
    USER* foundUser = NULL;
    USER keyUser;


    FILE* fp = fopen("userLeaderboard.txt", "r");
    for (int i = 0; i < numUsers; i++) {
        (*(users + i)).username = malloc(21);  // allocate for username
        fscanf(fp, "%[^,],%f;", (*(users + i)).username, &((*(users + i)).bestWPM));
    }

    fclose(fp);

    qsort(users, numUsers, sizeof(USER), compareUsersByName);
    
    keyUser.username = searchName;

    foundUser = (USER*)bsearch(&keyUser, users, numUsers, sizeof(USER), compareUsersByName);

    // Ispis rezultata
    if (foundUser != NULL) {
        printf("\nKorisnik: %s\nWPM: %.2f\n", foundUser->username, foundUser->bestWPM);
    }
    else {
        printf("\nKorisnik '%s' nije pronadjen!\n", searchName);
    }
    for (int i = 0; i < numUsers; i++) {
        free((*(users + i)).username);
    }
    free(users);
    users = NULL;

    printf("\nPritisni SPACE za nastavak.");
    do {
        letter = _getch();
    } while (letter != 32);
}