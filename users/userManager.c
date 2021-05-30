#include "userManager.h"

/**
  * Initialize the logged users array
  */
void initUsers() {
    initArray(&loggedUsers, 4);
}

/**
  * Adds a user to the logged users array and the historical
  * @param user {char*} user name to be added
  * @return {int} index in the array where the user was added
  */
int addUser(char* user) {
    int existingIndex = alreadyLogged(user);
    if (existingIndex != -1) {
        return existingIndex;
    }

    size_t len = 0;
    struct UserInfo loggedUser;

    char usersFile[] = "users/users.csv";
    char* buffer;

    FILE* users = fopen(usersFile,"a+");

    strcpy(loggedUser.name, user);
    loggedUser.score = 0;

    while (getline(&buffer, &len, users) != -1) {
        char* splittedLine = strtok(buffer, ",");
        if (strcmp(splittedLine, user) == 0) {
            char* splittedLine = strtok(NULL, ",");

            int userScore;
            sscanf(splittedLine, "%d", &userScore);
            loggedUser.score = userScore;
            existingIndex = 1;
        }
    }

    if (existingIndex != 1){
        strcat(user, ",0\n");
        fputs(user, users);
    }
    fclose(users);

    insertArray(&loggedUsers, &loggedUser);
    return loggedUsers.used - 1;
}

int alreadyLogged(char* user) {
    for(int userIndex = 0; userIndex < loggedUsers.used; userIndex++) {
        if (strcmp((*loggedUsers.array[userIndex]).name, user) == 0) {
            return userIndex;
        }
    }

    return -1;
}