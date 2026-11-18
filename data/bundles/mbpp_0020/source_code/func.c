#include <stdbool.h>

#include <assert.h>



bool func0(long long x) {
  if (x % 2 == 0) {
    return false;
  }
  if (x == 1) {
    return true;
  }
  x = x + 1;
  long long p = 0;
  while (x % 2 == 0) {
    x = x / 2;
    p = p + 1;
    if (p == x) {
      return true;
    }
  }
  return false;
}
