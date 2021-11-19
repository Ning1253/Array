#include "array.h"

Array* newArray() {
    // Create a new array and return a pointer to it. 
    Array* array = malloc(sizeof(Array));
    initArray(array);
    return array;
}

void initArray(Array* array) {
    // Set all of the elements in the array to zero.
    array->used = 0;
    array->capacity = 0;
    array->data = NULL;
}

void appendArray(Array* array, void* item) {
    // If the array has space, append "item" to the end of the array. 
    // Otherwise, resize the array by doubling its size. 
    // Or, if its current size is 0, set it to 8. 
    if (array->used < array->capacity) {
        array->data[array->used] = item;
        array->used++;
    } else {
        if (array->capacity) {
            resizeArray(array, 2 * array->capacity);
        } else {
            resizeArray(array, 8);
        }

        appendArray(array, item);
    }
}

void insertArray(Array* array, void* item, int index) {
    // Insert the item into the array by shifting all of the elements in the array 
    // after the given index along by 1 before adding the item. 
    // First check if the index is within the currently used array. 

    // Copy the last item, if it exists. 
    // If the index is the currently used amount, just append, if not, shove all items along. 
    if (index == array->used || index == -1) {
        appendArray(array, item);
    }
    else if (array->used) {
        index = modIndex(array, index);
        appendArray(array, array->data[array->used - 1]);
    

        // Shift all other elements over by 1. 
        for (int i = array->used - 2; i > index; i--) {
            array->data[i] = array->data[i - 1];
        }
        
        // Add the element. 
        array->data[index] = item;
    } else {
        index = modIndex(array, index); 
        // This will automatically crash the function if the index
        // is out of bounds. 
    }
}

void resizeArray(Array* array, int newsize) {
    // Set the new capacity of the array to "newsize". 
    array->capacity = newsize;
    array->data = realloc(array->data, array->capacity * sizeof(void*));

    if (array->used > array->capacity) array->used = array->capacity;
}

void* popArray(Array* array, int index) {
    // Read the value at the given index, and remove it from the array. 
    void* item = readArray(array, index);
    removeArray(array, index);

    return item;
}

void removeArray(Array* array, int index) {
    // Check if index is in bounds. 
    index = modIndex(array, index);

    for (int i = index; i < array->used - 1; i++) {
        array->data[i] = array->data[i + 1];
    }

    // Shrink the size of the array by 1. 
    array->used--;

    /* If the current capacity is higher than 8 but less than half of the array
       is being used, resize the array to half of its old capacity.             */
    if (array->capacity > 8 && 2 * array->used < array->capacity) {
        resizeArray(array, array->capacity / 2);
    } 
    else if (!array->used) {
        // If it is empty, wipe it and free the current pointer. 
        free(array->data);
        initArray(array);
    }
}

void* readArray(Array* array, int index) {
    // Once again if the index is out of bounds, crash. 
    index = modIndex(array, index);

    // Return the data at the position of the index after made positive. 
    return array->data[index];
}

void freeArray(Array* array) {
    // If the array exists, wipe it, free its data, free it. 
    // If not, do nothing. 
    if (array) {
        // For each item in the array, free it, delete it. 
        for (int i = 0; i < array->used; i++) {
            free(array->data[i]);
        }

        array->used = 0;
        array->capacity = 0;

        free(array->data);
        array->data = NULL;
        
        free(array);
    }
}

void deleteArray(Array* array) {
    // Re-initialise, then free, to avoid loss of data. 
    initArray(array);
    freeArray(array);
}

int modIndex(Array* array, int index) {
    // Make index fit within normal bounds, or crash. 
    if (index >= array->used || -index > array->used) {
        printf("Out of bounds error: Index out of range\n");
        exit(1);
    } else {
        return (array->used + index) % array->used;
    }
}