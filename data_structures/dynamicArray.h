/*
 * TEC, Cartago, Escuela de Ingeniería en Computación, Principios de Sistemas Operativos
 * Proyecto: TriviaCR
 * Abraham Meza Vega, 2018168174
 * Lindsay Morales Bonilla, 2018077301
 * 05/06/2021, I Semestre 2021, Prof. Esteban Arias Méndez
*/

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "userInfo.h"

/**
  * Data structure to hold dynamic array information
  */
struct DynamicArray {
  struct UserInfo **array;
  size_t used;
  size_t size;
};

void initArray(struct DynamicArray *array, size_t initialSize);
void insertArray(struct DynamicArray *array, struct UserInfo *user);
void freeArray(struct DynamicArray *array);

#endif