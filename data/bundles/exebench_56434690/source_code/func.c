#include <stdio.h>

void swap(int* m, int* n)
{
    int x =*m;
    *m =*n;
    *n =x;
}
