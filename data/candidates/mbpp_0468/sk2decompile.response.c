int func0(int *arr, int len) {
  int dp[len];
  for (int i = 0; i < len; i++) {
    dp[i] = arr[i];
  }
  for (int i = 1; i < len; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j] && dp[i] < arr[i] * dp[j]) {
        dp[i] = arr[i] * dp[j];
      }
    }
  }
  int max = dp[0];
  for (int i = 1; i < len; i++) {
    if (dp[i] > max) {
      max = dp[i];
    }
  }
  return max;
}