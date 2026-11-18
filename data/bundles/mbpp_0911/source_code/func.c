

#include <stdio.h>

#include <assert.h>



int func0(int nums[], int size) {
  int i, j, temp;
  if (size < 3) {
    return -1;
  }
  for (i = 0; i < size - 1; i++) {
    for (j = i + 1; j < size; j++) {
      if (nums[i] < nums[j]) {
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
      }
    }
  }
  int highest = nums[0];
  int second_highest = nums[1];
  int third_highest = nums[2];
  int lowest = nums[size - 1];
  int second_lowest = nums[size - 2];
  int product1 = highest * second_highest * third_highest;
  int product2 = highest * lowest * second_lowest;
  return (product1 > product2) ? product1 : product2;
}
