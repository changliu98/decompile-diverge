#include <stdio.h>

#include <ctype.h>

#include <string.h>

void Iswap (int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
