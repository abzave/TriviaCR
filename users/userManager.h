/*
 * TEC, Cartago, Escuela de Ingeniería en Computación, Principios de Sistemas Operativos
 * Proyecto: TriviaCR
 * Abraham Meza Vega, 2018168174
 * Lindsay Morales Bonilla, 2018077301
 * 05/06/2021, I Semestre 2021, Prof. Esteban Arias Méndez
*/

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "../data_structures/dynamicArray.h"

struct DynamicArray loggedUsers;

void initUsers();
int addUser(char*);
int alreadyLogged(char*);

#endif