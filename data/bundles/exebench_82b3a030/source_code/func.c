#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

int intwt(double N, double *W)
{
   int i;

   if (N < 1.0) {
      i = 1;
      *W = N;
   }
   if (N >= 1.0) {
      i = N;
      *W = 1.0;
   }
   return (i);
}
