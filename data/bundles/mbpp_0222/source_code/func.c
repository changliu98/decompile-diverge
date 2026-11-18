

#include <stdbool.h>

#include <assert.h>



bool func0(int* test_array, int size) {
  for (int i = 1; i < size; i++) {
    if (sizeof(test_array[i]) != sizeof(test_array[0])) {
      return false;
    }
  }
  return true;
}
