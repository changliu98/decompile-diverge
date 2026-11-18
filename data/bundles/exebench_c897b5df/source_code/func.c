#include <math.h>

#include <stdio.h>

#include <string.h>

void
mlVectorScaleTo(const float *a, float b, float *result)
{
 unsigned int i;

 for(i = 0; i < 3; i++)
  result[i] = a[i] * b;
}
