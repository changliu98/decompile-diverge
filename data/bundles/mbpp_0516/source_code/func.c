

#include <stdio.h>

#include <assert.h>

#include <stdlib.h>



#define RADIX 10



void func0(int *nums, int size) {
  int placement = 1;
  int max_digit = nums[0];
  for (int i = 1; i < size; i++) {
    if (nums[i] > max_digit) {
      max_digit = nums[i];
    }
  }
  int *output = (int *)malloc(size * sizeof(int));
  int *count = (int *)malloc(RADIX * sizeof(int));
  while (placement <= max_digit) {
    for (int i = 0; i < RADIX; i++) {
      count[i] = 0;
    }
    for (int i = 0; i < size; i++) {
      int index = (nums[i] / placement) % RADIX;
      count[index]++;
    }
    for (int i = 1; i < RADIX; i++) {
      count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
      int index = (nums[i] / placement) % RADIX;
      output[count[index] - 1] = nums[i];
      count[index]--;
    }
    for (int i = 0; i < size; i++) {
      nums[i] = output[i];
    }
    placement *= RADIX;
  }
  free(output);
  free(count);
}
