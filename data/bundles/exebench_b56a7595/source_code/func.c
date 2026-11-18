#include <stdio.h>

#include <stdlib.h>

void rotr(int *a,int *b,int *c)
{
    int num;
     num = *c;
    *c = *b;
    *b = *a;
    *a = num;
}
