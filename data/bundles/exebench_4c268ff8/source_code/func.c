#include <stdio.h>

#include <stdlib.h>

void swap_int(int *n, int *m)
{
    int temp = *n;
    *n = *m;
    *m = temp;
}
