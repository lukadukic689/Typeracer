#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "filetypes.h"
#include "functions.h"

char* wrongText = NULL;

int main() {
	
	path = NULL;
	path = memoryAlloc(MAX_PATH);
	

	FILE* fp = fopen("currentPath.txt", "r"); //loads last chosen text 

	fgets(path, MAX_PATH, fp);
	printf("%s", path);

	fclose(fp);

	char* username = NULL;
	username = memoryAlloc(20);

	fp = fopen("currentUser.txt", "r"); //loads last player

	fgets(username, 20, fp);
	printf("%s", username);

	fclose(fp);
	menu(path, username);
	free(path);
	path = NULL;
}