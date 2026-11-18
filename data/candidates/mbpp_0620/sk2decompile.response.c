int func0(int *nums, int numsSize) {
  int dp[numsSize];
  dp[numsSize - 1] = 1;
  for (int i = numsSize - 2; i >= 0; i--) {
    int max = 0;
    for (int j = i + 1; j < numsSize; j++) {
      if ((nums[j] % nums[i] == 0 || nums[i] % nums[j] == 0) &&
          dp[j] > max) {
        max = dp[j];
      }
    }
    dp[i] = max + 1;
  }
  int result = dp[0];
  for (int i = 1; i < numsSize; i++) {
    if (dp[i] > result) {
      result = dp[i];
    }
  }
  return result;
}