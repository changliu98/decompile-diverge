#include <string.h>

#include <stdlib.h>

#include <errno.h>

#include <math.h>

#include <float.h>

void complexMultiplicationRI(double *zReal, double *zImag, double xReal, double xImag, double yReal, double yImag)
{
 *zReal = xReal * yReal - xImag * yImag;
 *zImag = xReal * yImag + xImag * yReal;
}
