#include <stdio.h>

void twoValueSwap(float *valueA, float *valueB) {
    float temp = *valueA;
    *valueA = *valueB;
    *valueB = temp;
}
