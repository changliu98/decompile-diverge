int func0(int n) {
    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; ; ++i) {
        if (i >= n + 1)
            break;
        dp[i] = i;
        int j = 2;
        while (j <= i / j) {
            int t = dp[i / j] * dp[j];
            if (t > dp[i])
                dp[i] = t;
            ++j;
        }
    }
    return dp[n];
}