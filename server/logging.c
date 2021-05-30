#include "logging.h"

/**
  * Creates a new log file name to be used in the next log
  */
void prepareNewLog() {
    resetTime();

    strcpy(logName, "logs/");
    strcat(logName, buffer);
    strcat(logName, "_log.txt");
}

/**
  * Sets the current time to be used in the log
  */
void resetTime() {
    now = time(NULL);
    t = localtime(&now);
    strftime(buffer, sizeof(buffer) - 1, "%Y-%m-%d %H:%M", t);
}

/**
  * Writes in the log the string passed and adds the timestamp
  * @param log {char*}: String to be logged
  */
void logText(char* log) {
    char newEntry[1024];
    resetTime();

    strcpy(newEntry, "[");
    strcat(newEntry, buffer);
    strcat(newEntry, "] "); 
    strcat(newEntry, log);
    strcat(newEntry, "\n");

    currentLog = fopen(logName, "a+");
    fputs(newEntry, currentLog);
    fclose(currentLog);
}

/**
  * Writes in the log the a formatted string with a int
  * @param log {char*}: Formatted string to be logged
  * @param number {int}: value to replace in the format
  */
void logWithInt(char* log, int number) {
    char newEntry[1024];
    sprintf(newEntry,log,number);

    logText(newEntry);
}
