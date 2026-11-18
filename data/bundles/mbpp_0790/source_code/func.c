

#include <stdbool.h>

#include <assert.h>



bool func0(int nums[], int length) {
  for (int i = 0; i < length; i++) {
    if (nums[i] % 2 != i % 2) {
      return false;
    }
  }
  return true;
}
