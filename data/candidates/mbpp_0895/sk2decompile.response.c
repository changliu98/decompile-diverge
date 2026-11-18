int _rob(int *nums, int numsSize) {
  if (numsSize == 1) {
    return nums[0];
  }
  int dp[numsSize];
  dp[0] = nums[0];
  dp[1] = nums[0] > nums[1] ? nums[0] : nums[1];
  for (int i = 2; i < numsSize; i++) {
    int pre = dp[i - 1];
    int prepre = dp[i - 2] + nums[i];
    int cur = nums[i];
    dp[i] = pre > prepre ? pre : prepre;
    dp[i] = dp[i] > cur ? dp[i] : cur;
  }
  return dp[numsSize - 1];
}