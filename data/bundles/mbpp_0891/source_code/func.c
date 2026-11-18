#include <assert.h>

#include <stdbool.h>



bool func0(int A, int B) {
  while (A > 0 && B > 0) {
    A = A / 10;
    B = B / 10;
  }
  if (A == 0 && B == 0) {
    return true;
  }
  return false;
}
