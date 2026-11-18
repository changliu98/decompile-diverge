#include <math.h>

#include <stdio.h>

#include <stdlib.h>

void swap (float *min, float *max)
{
    float temp;

    if (*min > *max) {
        temp = *max;
        *max = *min;
        *min = temp;
    };
}
