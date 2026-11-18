#include <inttypes.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <tgmath.h>

#include <math.h>

#include <assert.h>

float vec_dot_prodf(const float x[], const float y[], int n)
{
    int i;
    float z;

    z = 0.0f;
    for (i = 0; i < n; i++)
        z += x[i]*y[i];
    return z;
}
