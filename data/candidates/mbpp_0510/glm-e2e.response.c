int func0(int* a, int b, int c) {
    int rows = c + 1;
    int cols = b + 1;
    int dp[rows][cols];

    for (int i = 0; i <= c; i++) {
        for (int j = 0; j <= b; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= c; i++) {
        for (int j = 1; j <= b; j++) {
            dp[i][j] = dp[i][j - 1];
            if (a[j - 1] <= i && a[j - 1] > 0) {
                dp[i][j] += dp[i / a[j - 1]][j - 1] + 1;
            }
        }
    }

    return dp[c][b];
}