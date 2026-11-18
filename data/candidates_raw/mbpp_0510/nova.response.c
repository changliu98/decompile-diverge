int func0(int *arr, int n, int m) {
    int i, j, k;
    int dp[n + 1][m + 1];
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            dp[j][i] = 0;
        }
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (arr[j - 1] <= i) {
                dp[j][i] = dp[j - 1][i] + 1;
            }
            if (arr[j - 1] <= i) {
                dp[j][i] = dp[j][i] + dp[j - 1][i / arr[j - 1]];
            }
        }
    }
    return dp[n][m];
}