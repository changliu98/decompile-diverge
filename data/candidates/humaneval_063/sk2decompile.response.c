int func0(int n) {
  int dp[100];
  int m = n;
  memset(dp, 0, sizeof(dp));
  dp[1] = 0;
  dp[2] = 1;
  for (int i = 3; i <= m; i++) {
    dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
  }
  return dp[m];
}