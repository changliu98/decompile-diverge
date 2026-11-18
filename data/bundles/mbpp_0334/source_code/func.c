

#include <assert.h>

#include <stdbool.h>



bool func0(int a, int b, int c) {
  if ((a + b <= c) || (a + c <= b) || (b + c <= a)) {
    return false;
  } else {
    return true;
  }
}
