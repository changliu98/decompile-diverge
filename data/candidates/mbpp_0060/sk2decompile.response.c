int _longest_increasing_subsequence(int *nums, int nums_size) {
  int *dp = (int *)malloc(nums_size * sizeof(int));
  int max = 0;
  for (int i = 0; i < nums_size; i++) {
    dp[i] = 1;
  }
  for (int i = 0; i < nums_size; i++) {
    for (int j = 0; j < i; j++) {
      if (abs(nums[i] - nums[j]) <= 1 && dp[i] < dp[j] + 1) {
        dp[i] = dp[j] + 1;
      }
    }
  }
  for (int i = 0; i < nums_size; i++) {
    if (max < dp[i]) {
      max = dp[i];
    }
  }
  free(dp);
  return max;
}