#include <stdio.h>
#include "array.h"

int main() {
    Array* array = newArray();
    Array* array2 = newArray();

    for (int i = 0; i < 100; i++) {
        appendArray(array, i);
        insertArray(array2, i, 0);
    }
    for (int i = 0; i < 100; i++) {
        printf("Nums: %d %d\nCurrent sizes:%d/%d, %d/%d\n", popArray(array, 0), readArray(array2, i), array->used,array->capacity,
            array2->used, array2->capacity);
    }

    freeArray(array2);
}