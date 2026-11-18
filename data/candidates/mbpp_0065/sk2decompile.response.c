int _sum(int *nums, int n) {
  int sum = 0;
  int i;
  for (i = 0; i < n; i++) {
    if (nums[i] < 0) {
      int len = -nums[i];
      sum += _sum(nums + i + 1, len);
      i += len - 1;
    } else {
      sum += nums[i];
    }
  }
  return sum;
}