#include <math.h>

#include <stdio.h>

#include <string.h>

void
mlVectorSub(float *a, const float *b)
{
 unsigned int i;

 for(i = 0; i < 3; i++)
  a[i] -= b[i];
}
