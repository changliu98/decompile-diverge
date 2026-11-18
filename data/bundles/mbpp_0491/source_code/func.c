

#include <stdio.h>

#include <assert.h>

#include <math.h>



double func0(double a, int n, double r) {
  double total = (a * (1 - pow(r, n))) / (1 - r);
  return total;
}
