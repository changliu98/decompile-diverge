

#include <assert.h>



int func0(int n) {
  int j = 0;
  int sm = 0;
  for (int i = 1; i <= n; i++) {
    j = (2 * i - 1);
    sm += (j * j * j * j * j);
  }
  return sm;
}
