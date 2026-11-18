#include <math.h>

#include <assert.h>



double func0(double r, double h) {
  double l = sqrt(r * r + h * h);
  double LSA = M_PI * r * l;
  return LSA;
}
