

#include <assert.h>



int func0(int m, int n) {
  if (n < m) {
    int temp = m;
    m = n;
    n = temp;
  }
  return n * (n + 1) * (3 * m - n + 1) / 6;
}
