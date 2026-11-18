int func0(int n, int a, int b, int c) {
  int i, j;
  int dp[n + 10];
  for (i = 0; i < n + 10; i++) {
    dp[i] = -1;
  }
  dp[0] = 0;
  for (i = 0; i <= n; i++) {
    if (dp[i] != -1) {
      if (i + a <= n) {
        j = dp[i] + 1 > dp[i + a] ? dp[i] + 1 : dp[i + a];
        dp[i + a] = j;
      }
      if (i + b <= n) {
        j = dp[i] + 1 > dp[i + b] ? dp[i] + 1 : dp[i + b];
        dp[i + b] = j;
      }
      if (i + c <= n) {
        j = dp[i] + 1 > dp[i + c] ? dp[i] + 1 : dp[i + c];
        dp[i + c] = j;
      }
    }
  }
  return dp[n];
}