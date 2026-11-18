

#include <assert.h>



int func0(int x, int y) {
  int z;
  if (x > y) {
    z = x;
  } else {
    z = y;
  }
  while (1) {
    if ((z % x == 0) && (z % y == 0)) {
      return z;
    }
    z += 1;
  }
}
