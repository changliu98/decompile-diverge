#include <stdlib.h>

#include <string.h>

#include <math.h>

void lamda2x(double *lamda, double *x, double *h, double *boxlo)
{
  x[0] = h[0]*lamda[0] + h[5]*lamda[1] + h[4]*lamda[2] + boxlo[0];
  x[1] = h[1]*lamda[1] + h[3]*lamda[2] + boxlo[1];
  x[2] = h[2]*lamda[2] + boxlo[2];
}
