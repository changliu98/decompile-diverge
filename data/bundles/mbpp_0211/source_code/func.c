

#include <stdio.h>

#include <assert.h>

#include <math.h>



int func0(int n) {
  if (n == 1) {
    return 1;
  }
  int count = pow(2, n - 2);
  return count;
}
