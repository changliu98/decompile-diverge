#include <assert.h>

#include <complex.h>

#include <math.h>



double func0(double a, double b) {
  double complex cn = a + b * I;
  double angle = carg(cn);
  return angle;
}
