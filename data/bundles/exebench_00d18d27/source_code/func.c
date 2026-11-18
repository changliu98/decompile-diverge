#include <stdlib.h>

float dotprod (float B[], float C[], int n)
{
  int i;
  float sum = 0;

#pragma omp target teams map(to: B[0:n], C[0:n])
#pragma omp distribute parallel for reduction(+:sum)
      for (i = 0; i < n; i++)
 sum += B[i] * C[i];

  return sum;
}
