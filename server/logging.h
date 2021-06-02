/*
 * TEC, Cartago, Escuela de Ingeniería en Computación, Principios de Sistemas Operativos
 * Proyecto: TriviaCR
 * Abraham Meza Vega, 2018168174
 * Lindsay Morales Bonilla, 2018077301
 * 05/06/2021, I Semestre 2021, Prof. Esteban Arias Méndez
*/

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