#include <stdio.h>

#include <stdlib.h>

#include <string.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
