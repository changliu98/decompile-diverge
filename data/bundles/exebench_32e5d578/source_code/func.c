#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

void intToBin(unsigned int n, int* binary){
    unsigned int mask = 1U << (8-1);
    int i;
    for (i = 0; i < 8; i++) {
        binary[i] = (n & mask) ? 1 : 0;
        n <<= 1;
    }
}
