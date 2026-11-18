

#include <assert.h>



int func0(int nums[], int length) {
  for (int i = 0; i < length; i++) {
    if (nums[i] % 2 != 0) {
      return nums[i];
    }
  }
  return -1;
}
