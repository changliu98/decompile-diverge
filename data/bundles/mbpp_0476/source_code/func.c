

#include <stdio.h>

#include <assert.h>

#include <limits.h>



int func0(int nums[], int size) {
  int max_num = INT_MIN;
  int min_num = INT_MAX;
  for (int i = 0; i < size; i++) {
    if (nums[i] > max_num) {
      max_num = nums[i];
    }
    if (nums[i] < min_num) {
      min_num = nums[i];
    }
  }
  return max_num + min_num;
}
