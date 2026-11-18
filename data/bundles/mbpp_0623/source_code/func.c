

#include <stdio.h>

#include <assert.h>

#include <math.h>  // For pow function



void func0(int nums[], int length, int n, int result[]) {
  for (int i = 0; i < length; i++) {
    result[i] = pow(nums[i], n);
  }
}
