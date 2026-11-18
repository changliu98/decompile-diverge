#include <stdio.h>

#include <stdlib.h>

void swap_float(float *n, float *m)
{
    float temp = *n;
    *n = *m;
    *m = temp;
}
