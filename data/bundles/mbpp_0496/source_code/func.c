

#include <stdio.h>

#include <stdlib.h>

#include <assert.h>

#include <string.h>

int compare(const void *a, const void *b) {

    return (*(int*)a - *(int*)b);

}



void func0(int nums[], int len, int n, int result[]) {
  qsort(nums, len, sizeof(int), compare);
  for (int i = 0; i < n; i++) {
    result[i] = nums[i];
  }
}
