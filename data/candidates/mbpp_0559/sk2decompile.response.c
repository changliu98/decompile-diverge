int _maxSubArray(int *nums, int numsSize) {
  int max = 0;
  int sum = 0;
  int i;
  for (i = 0; i < numsSize; i++) {
    sum += nums[i];
    if (sum < 0) {
      sum = 0;
    } else if (sum > max) {
      max = sum;
    }
  }
  return max;
}