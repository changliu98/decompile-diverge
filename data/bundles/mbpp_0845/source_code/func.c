

#include <assert.h>

#include <math.h>



int func0(int n) {
  if (n < 0) {
    return 0;
  }
  if (n <= 1) {
    return 1;
  }
  double x = (n * log10((double)n / M_E) + log10(2 * M_PI * n) / 2.0);
  return (int)floor(x) + 1;
}
