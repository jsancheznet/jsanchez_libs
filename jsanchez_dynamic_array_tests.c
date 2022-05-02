/*
  TODO List

  - ArrayPop is currently failing, reimplement whole dynamic array? i
    want to try implementation with minimal macro use.
 */
#include <assert.h>
#include <stdio.h>

#include "jsanchez_dynamic_array.h"

typedef struct _player
{
    int A;
    int B;
    int C;
} player;

int main(void)
{


    { // TEST: ArrayInit should have 0 size and 0 capacity
        player *Players;
        ArrayInit(Players);
        assert(ArraySize(Players) == 0);
        assert(ArrayCapacity(Players) == 0);
    }

    { // TEST: Push one item
        player *Players;
        player PlayerOne = {0};
        player PlayerTwo = {0};
        player PlayerThree = {0};
        ArrayInit(Players);
        ArrayPush(Players, PlayerOne);
        ArrayPush(Players, PlayerTwo);
        assert(ArraySize(Players) == 2);
        assert(ArrayCapacity(Players) == 2);
        ArrayPush(Players, PlayerThree);
        assert(ArraySize(Players) == 3);
        assert(ArrayCapacity(Players) == 4);
    }

    { // TEST: Pop one item
        player *Players;
        player PlayerOne = {0};
        player PlayerTwo = {1, 2, 3};
        player Popped;
        ArrayInit(Players);
        ArrayPush(Players, PlayerOne);
        ArrayPush(Players, PlayerTwo);
        ArrayPop(Players, &Popped);
        assert(Popped.A == 1 && Popped.B == 2 && Popped.C == 3);
    }

    { // TODO: Pop from an empty array
        // NOTE(Jorge): This fires an
        // assertion. I need to figure
        // out how to write a soft assertion routine so it can check
        // errors in a better way. In the meantime, uncomment this
        // line for the test.
        // player *Players;
        // ArrayInit(Players);
        // ArrayPop(Players, &Out);
        // player Out;
    }

    { // TEST: Check that the array is rezising upwards correctly
        player *Players;
        ArrayInit(Players);
        player PlayerOne = {0};
        player PlayerTwo = {0};
        player PlayerThree = {0};
        player PlayerFour = {0};
        player PlayerFive = {0};
        ArrayPush(Players, PlayerOne);
        ArrayPush(Players, PlayerTwo);
        ArrayPush(Players, PlayerThree);
        ArrayPush(Players, PlayerFour);
        ArrayPush(Players, PlayerFive);
        assert(ArrayCapacity(Players) == 8);
    }

    { // TEST: Check that the array is resizing downwards correctly
        player *Players;
        player PlayerOne = {0};
        player PlayerTwo = {0};
        player PlayerThree = {0};
        player PlayerFour = {0};
        player PlayerFive = {0};
        player PlayerSix = {0};
        player Out = {0};
        ArrayInit(Players);
        ArrayPush(Players, PlayerOne);
        ArrayPush(Players, PlayerTwo);
        ArrayPush(Players, PlayerThree);
        ArrayPush(Players, PlayerFour);
        ArrayPush(Players, PlayerFive);
        ArrayPush(Players, PlayerSix);
        ArrayPop(Players, &Out);
        ArrayPop(Players, &Out);
        ArrayPop(Players, &Out);
        ArrayPop(Players, &Out);
        assert(ArrayCapacity(Players) == 4);
        ArrayPop(Players, &Out);
        assert(ArrayCapacity(Players) == 2);
    }

    { // TEST: ArrayFree
        player *Players;
        ArrayInit(Players);
        player PlayerOne = {0};
        player PlayerTwo = {0};
        player PlayerThree = {0};
        player PlayerFour = {0};
        player PlayerFive = {0};
        ArrayPush(Players, PlayerOne);
        ArrayPush(Players, PlayerTwo);
        ArrayPush(Players, PlayerThree);
        ArrayPush(Players, PlayerFour);
        ArrayPush(Players, PlayerFive);
        ArrayFree(Players);
        assert(Players == NULL);
    }
}
