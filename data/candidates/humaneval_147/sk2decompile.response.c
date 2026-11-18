int func0(int n) {
  int *a = malloc(n * sizeof(int));
  int **dp = malloc((n + 1) * sizeof(int *));
  int **dp2 = malloc((n + 1) * sizeof(int *));
  for (int i = 0; i <= n; i++) {
    dp[i] = calloc(3, sizeof(int));
    dp2[i] = calloc(3, sizeof(int));
  }
  dp[0][2] = 0;
  dp[0][1] = 0;
  dp[0][0] = 0;
  dp2[0][2] = 0;
  dp2[0][1] = 0;
  dp2[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    a[i - 1] = (i * i - i + 1) % 3;
    for (int j = 0; j < 3; j++) {
      dp[i][j] = dp[i - 1][j];
    }
    dp[i][a[i - 1]]++;
  }
  for (int k = 1; k < 3; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < 3; j++) {
        dp2[i][j] = dp2[i - 1][j];
      }
      if (i >= 1) {
        for (int j = 0; j < 3; j++) {
          dp2[i][(j + a[i - 1]) % 3] += dp[i - 1][j];
        }
      }
    }
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < 3; j++) {
        dp[i][j] = dp2[i][j];
        dp2[i][j] = 0;
      }
    }
  }
  int res = dp[n][0];
  for (int i = 0; i <= n; i++) {
    free(dp[i]);
    free(dp2[i]);
  }
  free(dp);
  free(dp2);
  free(a);
  return res;
}