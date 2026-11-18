int func0(int *arr, int n) {
    int dp[n];
    dp[n - 1] = 1;
    
    for (int i = n - 2; i >= 0; i--) {
        int max_len = 0;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] % arr[j] == 0 || arr[j] % arr[i] == 0) {
                if (dp[j] > max_len) {
                    max_len = dp[j];
                }
            }
        }
        dp[i] = max_len + 1;
    }
    
    int ans = dp[0];
    for (int i = 1; i < n; i++) {
        if (dp[i] > ans) {
            ans = dp[i];
        }
    }
    
    return ans;
}