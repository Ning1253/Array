#include <stdio.h>
#include "array.h"

ADD_ARRAY(int, Int)
ADD_ARRAY(char*, String)

int main() {
    Array* array = newArray();
    Array* array2 = newArray();
    Array* strarr = newArray();

    for (int i = 0; i < 100; i++) {
        appendArrayString(strarr, "abcdefg");
        appendArrayInt(array, i);
        insertArrayInt(array2, i, 0);
    }
    for (int i = 0; i < 100; i++) {
        printf("Nums: %d %d\nCurrent sizes:%d/%d, %d/%d\nString: %d\n", popArrayInt(array, 0), readArrayInt(array2, i), array->used,array->capacity,
            array2->used, array2->capacity, readArray(strarr, i));
    }

    freeArray(array2);
}