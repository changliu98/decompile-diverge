#include <math.h>

#include <stdio.h>

#include <string.h>

float
mlVectorDotProduct(const float *a, const float *b)
{
 return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
