int func0(int *coins, int n) {
    int *dp;
    int res;
    int i, j;
    int temp;

    if (n == 0 || coins[0] == 0) {
        res = 0x7fffffff;
        return res;
    }

    dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        res = 0x7fffffff;
        return res;
    }

    dp[0] = 0;
    for (i = 1; i < n; i++) {
        dp[i] = 0x7fffffff;
        for (j = 0; j < i; j++) {
            if (i < coins[j] || dp[j] == 0x7fffffff) {
                continue;
            }
            if (dp[i] < dp[j] + 1) {
                temp = dp[i];
            } else {
                temp = dp[j] + 1;
            }
            dp[i] = temp;
        }
    }

    res = dp[n - 1];
    free(dp);
    return res;
}