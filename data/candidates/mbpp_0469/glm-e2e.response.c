int func0(int *arr, int n, int k) {
    int i, j, l;
    int max_val, current_val, result;
    int **dp = (int **)malloc((k + 1) * sizeof(int *));
    for (i = 0; i <= k; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
    }

    for (i = 0; i <= k; i++) {
        for (j = 0; j < n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else {
                max_val = 0;
                for (l = 0; l < j; l++) {
                    current_val = arr[j] - arr[l] + dp[i - 1][l];
                    if (max_val < current_val) {
                        max_val = current_val;
                    }
                }
                if (dp[i][j - 1] > max_val) {
                    result = dp[i][j - 1];
                } else {
                    result = max_val;
                }
                dp[i][j] = result;
            }
        }
    }

    result = dp[k][n - 1];
    
    for (i = 0; i <= k; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}