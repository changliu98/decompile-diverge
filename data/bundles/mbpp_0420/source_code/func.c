

#include <assert.h>



int func0(int n) {
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += (2 * i) * (2 * i) * (2 * i);
  }
  return sum;
}
