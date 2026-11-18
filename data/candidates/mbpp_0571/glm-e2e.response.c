int func0(int *arr, int n, int k) {
    qsort(arr, n, 4, cmpfunc);
    
    int *dp = malloc(n * 4);
    dp[0] = 0;
    
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - 1];
        if (arr[i] - arr[i - 1] < k) {
            if (i >= 2) {
                if (dp[i] > dp[i - 2] + arr[i] + arr[i - 1]) {
                    dp[i] = dp[i];
                } else {
                    dp[i] = dp[i - 2] + arr[i] + arr[i - 1];
                }
            } else {
                if (dp[i] > arr[i] + arr[i - 1]) {
                    dp[i] = dp[i];
                } else {
                    dp[i] = arr[i] + arr[i - 1];
                }
            }
        }
    }
    
    int result = dp[n - 1];
    free(dp);
    return result;
}