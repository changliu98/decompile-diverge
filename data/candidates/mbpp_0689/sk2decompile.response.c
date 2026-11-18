int func0(int* nums, int numsSize) {
  int dp[numsSize];
  int i, j, ret, min;
  if (numsSize == 0 || nums[0] == 0) {
    min = 2147483647;
    ret = 1;
  } else {
    dp[0] = 0;
    for (j = 1; j < numsSize; j++) {
      dp[j] = 2147483647;
      for (i = 0; i < j; i++) {
        if (i + nums[i] >= j && dp[i] != 2147483647) {
          dp[j] = dp[j] < dp[i] + 1 ? dp[j] : dp[i] + 1;
          break;
        }
      }
    }
    min = dp[numsSize - 1];
    ret = 1;
  }
  return min;
}