#include <stdio.h>

#include <stdlib.h>

void change (int *p, int *q)
{
   int temp;
   temp = *p; *p = *q; *q = temp;
}
