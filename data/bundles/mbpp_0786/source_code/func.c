

#include <assert.h>

#include <stdlib.h>



int func0(int* a, int n, int x) {
  int i = 0;
  for (; i < n; i++) {
    if (a[i] > x) {
      break;
    }
  }
  return i;
}
