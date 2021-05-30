#ifndef LOGGING_H
#define LOGGING_H

#include <time.h>
#include <stdio.h>
#include <string.h>

char buffer[100];
char logName[100];
char usersFile[100];

time_t now;
struct tm *t;
FILE* currentLog;

void prepareNewLog();
void resetTime();
void logText(char*);
void logWithInt(char*, int);

#endif