int func0(int *nums, int n, int k)
{
    int dp[211][221];
    int i, j;
    for (i = 0; i <= k; ++i)
        for (j = 0; j <= n; ++j)
            dp[i][j] = 0;
    for (i = 1; i <= k; ++i)
        for (j = 1; j <= n; ++j) {
            dp[i][j] = dp[i][j - 1];
            if (i >= nums[j - 1] && nums[j - 1] > 0)
                dp[i][j] += dp[i / nums[j - 1]][j - 1] + 1;
        }
    return dp[k][n];
}