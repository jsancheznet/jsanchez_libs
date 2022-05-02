/*
	HOWTO USE
	
	#include "jsanchez_dynamic_array.h"

	// Create a pointer with the desired array type
	my_struct *StructArray;

	// Init the array, this allocates size for the array metadata and sets the array size and capacity to 0
	ArrayInit(StructArray);

	// Push to the end of the array, the array grows dynamically and each
	// time the capacity is reached it allocates the double of the space used
	// and copies everything onto the new memory pool
	my_struct Foo;
	ArrayPush(StructArray, Foo);

	// Pops the last element of the array. The array also resized down
	// when the size is 1/3 of the capacity and you pop one element.
	my_struct *Foo;
	ArrayPop(StructArray, &Foo);

	// Get the current array size and capacity, ArrayCount is the same as
	// ArraySize, i prefer ArrayCount but Size might be clearer
	int Size = ArraySize(StructArray);
	int Capacity = ArrayCapacity(StructArray);

	// Free the memory and metadata
	ArrayFree(StructArray);



  TODO List

  - Make the user setup defines so they can choose the function names so it better fits with their coding style.
      - Example: rename ArrayInit to __jsanchez_Array_Init and make the user do #define ArrayInit __jsanchez_ArrayInit
 */

#pragma once

// NOTE(Jorge): This only compiles in C

#include <stdlib.h>
#include <assert.h>

#define ArrayCount(ARR) (*((int *) ARR - 2))
#define ArraySize(ARR) (*((int *) ARR - 2))
#define ArrayCapacity(ARR) (*((int *) ARR - 1))

// Allocates space for the array metadata and sets the Size and Capacity to 0.
#define ArrayInit(ARRAY)                        \
    do {                                        \
        int *Raw = malloc(2 * sizeof(int));     \
        assert(Raw);                            \
        Raw[0] = 0;                             \
        Raw[1] = 0;                             \
        ARRAY = (void*)&Raw[2];                 \
    } while(0)                                  \

// 1- Check if ARRAY is valid
// 2- Set Raw Pointer
// 3- Free
// 4- Set ARRAY to NULL
#define ArrayFree(ARRAY)                        \
    do {                                        \
        assert(ARRAY);                          \
        int *Raw = ((int*)(ARRAY) - 2);         \
        free(Raw);                              \
        ARRAY = NULL;                           \
    } while(0)                                  \

// 1- Set Raw ptr, Raw[0] == ArraySize | Raw[1] == ArrayCapacity
// 2- ArraySize + 1
#define ArrayPush(ARRAY, VALUE)                                         \
    do {                                                                \
        int *Raw = ((int*)(ARRAY) - 2);                                 \
        Raw[0] = Raw[0] + 1;                                            \
        if(Raw[1] == 0)                                                 \
        {                                                               \
            Raw[1] = 1;                                                 \
            Raw = realloc(Raw, 2 * sizeof(int) + Raw[1] * sizeof((VALUE))); \
            assert(Raw);                                                \
            (ARRAY) = (void*)&Raw[2];                                   \
        }                                                               \
        if(Raw[0] > Raw[1])                                             \
        {                                                               \
            Raw[1] = 2 * Raw[1];                                        \
            Raw = realloc(Raw, 2 * sizeof(int) + Raw[1] * sizeof((VALUE))); \
            assert(Raw);                                                \
            (ARRAY) = (void*)&Raw[2];                                   \
        }                                                               \
        ARRAY[Raw[0] - 1] = (VALUE);                                    \
    } while(0)                                                            \


// 1- Verify ARRAY is valid
// 2- Verify OUT is valid
// 3- Set Raw pointer, Raw[0] == Size | Raw[1] == Capacity
// 4- Make sure we are not trying to pop an empty array
// 5- If Array Size > 0, set OUT to the last items in the array
// 6- Decrement Array Size by 1
// 7- If ArraySize <= ArrayCapacity/3 realloc and copy
// 8- If ArraySize <= 1/4 of ArrayCapacity, realloc to be ArraySize * 2 * sizeof(Type) + Raw
#define ArrayPop(ARRAY, OUT)                                        \
    do  {                                                           \
        assert(ARRAY);                                              \
        assert(OUT);                                                \
        int *Raw = ((int*)(ARRAY) - 2);                             \
        if(Raw[0] == 0)                                             \
        {                                                           \
            *(OUT) = NULL;                                          \
        }                                                           \
        else if(Raw[0] > 0)                                         \
        {                                                           \
            (*(OUT)) = ARRAY[Raw[0] - 1];                           \
            Raw[0] -= 1;                                            \
                                                                    \
            if(Raw[0] <= Raw[1]/4)                                  \
            {                                                       \
                Raw = realloc(Raw, 2 * sizeof(int) + Raw[0] * 2 * sizeof(*(OUT))); \
                assert(Raw);                                            \
            }                                                       \
        }                                                           \
    } while(0)                                                      \
