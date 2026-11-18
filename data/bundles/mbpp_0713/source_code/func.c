

#include <stdbool.h>

#include <assert.h>



bool func0(bool test_tup[], int size) {
  for (int i = 0; i < size; i++) {
    if (!test_tup[i]) return false;
  }
  return true;
}
