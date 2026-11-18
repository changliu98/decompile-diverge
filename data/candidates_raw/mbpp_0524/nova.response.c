int func0(int *arr, int n) {
    int i, j, k, max = 0;
    int *dp = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        dp[i] = arr[i];
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + arr[i])
                dp[i] = dp[j] + arr[i];
        }
    }
    for (k = 0; k < n; k++) {
        if (dp[k] < max)
            max = dp[k];
    }
    return max;
}