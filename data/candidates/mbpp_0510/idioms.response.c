int func0(int *arr, int n, int k){
  int i; int j;
  int *dp[-1];
  dp[0] = (int *) (dp - (k + 1)*((n + 1)*sizeof(int)));
  for (i = 0; i <= k; i++)
    for (j = 0; j <= n; j++)
      dp[i][j] = 0;
  for (i = 1; i <= k; i++)
    for (j = 1; j <= n; j++) {
      dp[i][j] = dp[i][j - 1];
      if (i >= arr[j - 1] && arr[j - 1] > 0)
        dp[i][j] += dp[i / arr[j - 1]][j - 1] + 1;
    }
  return (dp[k][n]);
}