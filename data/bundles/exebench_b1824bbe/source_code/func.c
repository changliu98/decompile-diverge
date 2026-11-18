#include <stdio.h>

#include <stdlib.h>

void swap3 (int * a, int * b)
{
  int k = * a;
  a = b;
  * b = k;
}
