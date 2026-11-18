#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <unistd.h>

#include <stdint.h>

#include <string.h>

void passByPointer(int * x)
{
    (*x) = 4;
    (*x) *= 4;

    return;
}
