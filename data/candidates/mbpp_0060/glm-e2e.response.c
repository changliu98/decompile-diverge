int func0(int *arr, int n) {
    int *dp = (int *)malloc(n * sizeof(int));
    int max = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) <= 1 && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        if (max < dp[k]) {
            max = dp[k];
        }
    }

    free(dp);
    return max;
}