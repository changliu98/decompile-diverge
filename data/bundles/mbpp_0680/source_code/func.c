

#include <stdbool.h>

#include <assert.h>



bool func0(int nums[], int size) {
  for (int i = 0; i < size - 1; i++) {
    if (nums[i] > nums[i + 1]) {
      return false;
    }
  }
  return true;
}
