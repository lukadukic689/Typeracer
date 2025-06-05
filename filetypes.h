#ifndef FILETYPES_H
#define FILETYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

typedef struct USER {
	char* username;
	float bestWPM;
} USER;

char* text;
char* typedText;
char* path;
char* unsolvedText;
char* correctText;
char* wrongText;


#endif //FILETYPES_H