/*
array.h - library header file for array.lib. 
Funcs:
    newArray() - returns an array pointer to a newly created array struct. 
    appendArray(Array* array, void* item) - adds the item to the end of the array. 
    insertArray(Array* array, void* item, int index) - inserts the item at the specified index. 
    popArray(Array* array, int index) - removes the item at the specified index, and returns it. 
    removeArray(Array* array, int index) - like pop, but without returning the item. 
    readArray(Array* array, int index) - returns the item at the specified index, without removing it. 
    freeArray(Array* array) - free the array pointer - the array is destroyed by this, obviously. 

Technical Funcs (only for specific use cases):
    resizeArray(Array* array, int newsize) - resize the array to newsize with no side effects, 
        apart from removing the items after the resize. 
    modIndex(Array* array, int index) - essentially verifies if the index is valid for the given 
        array - if it isn't, the program will exit with an error. If it is, the function will
        return the index, making it a positive one if it was negative beforehand. 
*/
#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Array {
    int used;
    int capacity;
    void** data;
} Array;

Array* newArray();
void initArray(Array* array);
void resizeArray(Array* array, int newsize);

void appendArray(Array* array, void* item);
void insertArray(Array* array, void* item, int index);

void* popArray(Array* array, int index);
void removeArray(Array* array, int index);
void* readArray(Array* array, int index);

void freeArray(Array* array);

int modIndex(Array* array, int index);