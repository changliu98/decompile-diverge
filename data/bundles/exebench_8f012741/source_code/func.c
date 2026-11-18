#include <stdio.h>

#include <stddef.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

#include <float.h>

#include <stdio.h>

static void lin_solve_2(double x[2], const double A[4], const double y[2])
{
  const double idet = 1/(A[0]*A[3] - A[1]*A[2]);
  x[0] = idet*(A[3]*y[0] - A[1]*y[1]);
  x[1] = idet*(A[0]*y[1] - A[2]*y[0]);
}
