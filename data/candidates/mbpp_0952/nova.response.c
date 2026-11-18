int func0(int n, int k, int mod) {
    int i, j, t;
    int dp[k + 1];
    if (k > n - k)
        k = n - k;
    for (i = 0; i <= k; i++)
        dp[i] = 0;
    dp[0] = 1;
    for (i = 1; i <= n; i++) {
        if (i < k)
            t = i;
        else
            t = k;
        for (j = t; j >= 1; j--)
            dp[j] = (dp[j] + dp[j - 1]) % mod;
    }
    return dp[k];
}