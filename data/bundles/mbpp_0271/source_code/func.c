

#include <assert.h>



long func0(int n) {
  long sum = 0;
  for (int i = 1; i <= n; i++) {
    int j = 2 * i;
    sum += j * j * j * j * j;
  }
  return sum;
}
