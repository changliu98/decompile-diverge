#include <stdlib.h>

#include <string.h>

#include <math.h>

#include <float.h>

void complexMultiplication(double xReal, double xImag, double yReal, double yImag, double *zReal, double *zImag)
{
 *zReal = xReal * yReal - xImag * yImag;
 *zImag = xReal * yImag + xImag * yReal;
}
