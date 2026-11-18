

#include <assert.h>

#include <stdbool.h>



bool func0(const int* nums, int size) {
  for (int i = 0; i < size; i++) {
    if (nums[i] % 2 != i % 2) {
      return false;
    }
  }
  return true;
}
