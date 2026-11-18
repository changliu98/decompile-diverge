#include <stdlib.h>

void
foo (int *x, int *y)
{
#pragma omp target map (alloc:x[0]) map (alloc:y[0:8])
  {
    int i;
    for (i = 0; i < 8; i++)
      if (y[i] != 2 + i)
 break;
    if (i != 8 || *x != 1)
      *x = 6;
    else
      {
 *x = 8;
 for (i = 0; i < 8; i++)
   y[i] = 9 + i;
      }
  }
#pragma omp target update from (y[0:8]) from (x[0])
}
