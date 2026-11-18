int func0(int *arr, int n) {
    int i, j, k, l, m, max;
    int dp[n];
    dp[n - 1] = 1;
    for (i = n - 2; i >= 0; i--) {
        max = 0;
        for (j = i + 1; j < n; j++) {
            if (arr[j] % arr[i] == 0 || arr[i] % arr[j] == 0) {
                if (dp[j] > max) {
                    max = dp[j];
                }
            }
        }
        dp[i] = max + 1;
    }
    max = dp[0];
    for (i = 1; i < n; i++) {
        if (dp[i] > max) {
            max = dp[i];
        }
    }
    return max;
}