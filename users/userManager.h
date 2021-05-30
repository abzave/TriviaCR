#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "../data_structures/dynamicArray.h"

struct DynamicArray loggedUsers;

void initUsers();
int addUser(char*);
int alreadyLogged(char*);

#endif