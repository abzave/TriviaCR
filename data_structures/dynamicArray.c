#include "dynamicArray.h"

/**
  * Dynamic array instantiation function
  * @param array {struct DynamicArray} reference to the array to be instantiated
  * @param initialSize {size_t} size that the array will have initially
  */
void initArray(struct DynamicArray *array, size_t initialSize) {
  array->array = malloc(initialSize * sizeof(int));
  array->used = 0;
  array->size = initialSize;
}

/**
  * Add new element to the array. If the array is full it is realocated and the size is doubled
  * @param array {struct DynamicArray} reference to the array to be used
  * @param initialSize {size_t} element to be added
  */
void insertArray(struct DynamicArray *array, struct UserInfo *user) {
  if (array->used == array->size) {
    array->size *= 2;
    array->array = realloc(array->array, array->size * sizeof(struct UserInfo*));
  }
  array->array[array->used++] = user;
}

/**
  * Free the memory used by the array
  * @param array {struct DynamicArray} reference to the array to be free
  */
void freeArray(struct DynamicArray *array) {
  free(array->array);
  array->array = NULL;
  array->used = array->size = 0;
}