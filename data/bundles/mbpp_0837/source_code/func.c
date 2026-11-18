

#include <assert.h>



int func0(int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += (2 * i + 1) * (2 * i + 1) * (2 * i + 1);
  }
  return sum;
}
