int func0(int *arr, int n) {
    if (n == 1) {
        return arr[0];
    }

    int dp[n];
    dp[0] = arr[0];
    dp[1] = (arr[0] > arr[1]) ? arr[0] : arr[1];

    for (int i = 2; i < n; i++) {
        int prev = dp[i - 1];
        int prev_prev_plus_curr = dp[i - 2] + arr[i];
        int curr = arr[i];

        dp[i] = (prev > prev_prev_plus_curr) ? prev : prev_prev_plus_curr;
        dp[i] = (dp[i] > curr) ? dp[i] : curr;
    }

    return dp[n - 1];
}