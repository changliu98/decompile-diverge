#include <assert.h>

#include <stdio.h>



char* func0(int seq_nums[], int n) {
  int diff[n - 1];
  for (int x = 1; x < n; x++) {
    diff[x - 1] = seq_nums[x] - seq_nums[x - 1];
  }
  for (int i = 1; i < n - 1; i++) {
    if (diff[i] != diff[0]) {
      return "Non Linear Sequence";
    }
  }
  return "Linear Sequence";
}
