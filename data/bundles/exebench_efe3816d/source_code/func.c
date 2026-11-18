#include  <stdio.h>

#include  <stdlib.h>

long int metric( double* x, double* y, double* z, double* M )
{
   int i;

   for( i=0; i<9; i++) M[i] = 0;
   M[0] = M[4] = M[8] = 1;

   return 0;
}
