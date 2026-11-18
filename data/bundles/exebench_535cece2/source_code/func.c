#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <assert.h>

void copy_dice(int* dice, int* copy)
{
    int i;
    for (i=0; i<6; i++){
        copy[i] = dice[i];
    }
}
