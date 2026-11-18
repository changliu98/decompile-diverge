bool _3sum(int nums[], int numsSize, int target, int result[]) {
  int i, j, k;
  for (i = 0; i < numsSize - 2; i++) {
    for (j = i + 1; j < numsSize - 1; j++) {
      for (k = j + 1; k < numsSize; k++) {
        if (nums[i] + nums[j] + nums[k] == target) {
          result[0] = nums[i];
          result[1] = nums[j];
          result[2] = nums[k];
          return true;
        }
      }
    }
  }
  return false;
}