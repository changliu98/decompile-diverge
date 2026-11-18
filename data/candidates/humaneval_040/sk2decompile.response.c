bool _3Sum(int* nums, int numsSize) {
  int i, j, k;
  for (i = 0; i < numsSize; i++) {
    for (j = i + 1; j < numsSize; j++) {
      for (k = j + 1; k < numsSize; k++) {
        if (nums[i] + nums[j] + nums[k] == 0) {
          return true;
        }
      }
    }
  }
  return false;
}