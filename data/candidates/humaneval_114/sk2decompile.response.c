long _min_subarray(int* nums, int numsSize) {
  int i;
  long sum = nums[0];
  long min = nums[0];
  for (i = 1; i < numsSize; i++) {
    sum = sum < 0 ? sum + nums[i] : nums[i];
    if (sum < min) min = sum;
  }
  return min;
}