

#include <assert.h>

#include <stdbool.h>



bool func0(int x, int y, int z) {
  if (x != y && y != z && z != x) {
    return true;
  } else {
    return false;
  }
}
