

#include <math.h>

#include <assert.h>



double func0(int a, int b) {
  if (a < 0 || b < 0) {
    return -1;
  }
  double area = (3 * sqrt(3) * pow(a, 2)) / (4 * b);
  return area;
}
