#include <stdio.h>

#include <stdlib.h>

#include <time.h>

void swap (int *x, int *y){

    if(x == NULL || y== NULL) return;

    int temp = *x;
    *x = *y;
    *y= temp;

    return ;
}
