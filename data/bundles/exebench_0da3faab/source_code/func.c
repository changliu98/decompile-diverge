#include <malloc.h>

#include <string.h>

#include <stdio.h>

static void mac_real(float *x, float *h, float *y)
{
 y[0] += x[0] * h[0];
 y[1] += x[1] * h[0];
}
