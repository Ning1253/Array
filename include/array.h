/*
array.h - library header file for array.lib. 
Funcs:
    newArray() - returns an array pointer to a newly created array struct. 
    appendArray(Array* array, void* item) - adds the item to the end of the array. 
    insertArray(Array* array, void* item, int index) - inserts the item at the specified index. 
    popArray(Array* array, int index) - removes the item at the specified index, and returns it. 
    removeArray(Array* array, int index) - like pop, but without returning the item - does not free the memory the 
        pointer was pointing to. 
    readArray(Array* array, int index) - returns the item at the specified index, without removing it. 
    freeArray(Array* array) - free the array pointer - the array is destroyed by this, obviously - and so is
        all data which the pointers in the array were pointing to. This is an "end of program" function. 
    ADD_ARRAY(type, name) - create a new set of functions to append items of type "type", with each function
        being named eg. readArrayname(), insertArrayname() etc. (for example:
            ADD_ARRAY(int, Int) will create a few functions, one of which is 
            appendArrayInt(Array* array, int item))

            The removeArrayname() and popArrayname() functions will also free the memory which the respective pointer
                was pointing to, as opposed to removeArray() and popArray() which is only manipulating the array itself. 

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

#define ADD_ARRAY(type, name) \
    void appendArray##name(Array* array, type item) { \
        type* ptr = malloc(sizeof(type)); \
        *ptr = item; \
        appendArray(array, ptr); \
    } \
    \
    void insertArray##name(Array* array, type item, int index) { \
        type* ptr = malloc(sizeof(type)); \
        *ptr = item; \
        insertArray(array, ptr, index); \
    } \
    \
    type popArray##name(Array* array, int index) { \
        type* ptr = malloc(sizeof(type)); \
        void* tofree = popArray(array, index); \
        *ptr = *(type*)tofree; \
        free(tofree); \
        return *ptr; \
    } \
    \
    void removeArray##name(Array* array, int index) { \
        free(popArray(array, index)); \
    } \
    \
    type readArray##name(Array* array, int index) { \
        type* ptr = malloc(sizeof(type)); \
        *ptr = *(type*)readArray(array, index); \
        return *ptr; \
    }
