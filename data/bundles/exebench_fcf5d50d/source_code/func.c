#include <math.h>

#include <assert.h>

#include <float.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

void mult_add_into_cpu(int N, float *X, float *Y, float *Z)
{
    int i;
    for(i = 0; i < N; ++i) Z[i] += X[i]*Y[i];
}
