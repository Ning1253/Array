# LibArrayC
A C library + header compiled for Windows (although source is written using the standard library only, so it can be used in any project). It contains most of the functions one would expect mutable arrays to have, and includes macros for the ability to add non-pointer objects to arrays.

This is achieved through copying the item as it is created, storing its pointer into the array. The copied item can be accessed through its pointer, or through a second function designed to return the contents of the pointer directly. 

## Basic Usage
#### `Array* newArray()`

- Creates a new Array struct and returns a pointer to it.

#### `void appendArray(Array* array, void* item)`

- Appends the void pointer `item` to the end of the array. 

#### `void insertArray(Array* array, void* item, int index)`

- Inserts the void pointer `item` at the given index, shifting all following items along by one. 

#### `void* readArray(Array* array, int index)`

- Returns the pointer at the given index of the array. 

#### `void* popArray(Array* array, int index)`

- Returns the pointer at the given index of the array, and removes it from the array. 

#### `void removeArray(Array* array, int index)`

- Removes the item at the given index from the array. 

#### `void initArray(Array* array)`

- Reset the array to its initial state. 

#### `void freeArray(Array* array)`

- Free the array itself. *(In the future [probably in a few days] this will also free each of the pointers within the array - the idea being that an array should only be freed once it has completely finished its usage. There already exists a way to remove specific items from the array without freeing them of course, so this is really something to be called at the end of the program to avoid memory leaks, and not for any other reason)*

## Usage with non-pointer types

#### Macro: `ADD_ARRAY(type, name)`

- This macro creates a set of functions designed to manipulate items of type `type` and moving them into and out of arrays - for example creating a for loop with an integer counting up and calling the alternative functions would allow for each integer to be added to the array seperately, instead of the pointer to the loop variable being copied to the array multiple times. `name` sets the suffix to add at the end of the function names:
  - `void appendArrayname(Array* array, type item)`
  - `void insertArrayname(Array* array, type item, int index)`
  - `type readArrayname(Array* array, int index)`
  - `type popArrayname(Array* array, int index)`
  - `type removeArrayname(Array* array, int index)` 

- The last three functions actually free the copy of the item created instead of simply removing the pointer from the array - so these should be used in most use-cases. 

## Example usage:

```C
#include <stdio.h>
#include "array.h"

ADD_ARRAY(int, Int)

int main() {
  Array* array = newArray(); // Create new array
  
  for (int i = 0; i < 20; i++) {
    appendArrayInt(array, i); // Append i from i = 0 to 19 into the array. 
    printf("%d ", readArrayInt(array, -1)); // Print the last item from the array. 
  }
  
  // freeArray(Array* array); // Free the array and all of its data (coming soon)
}
```
```
Output:
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
```
