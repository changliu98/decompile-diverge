int func0(int n, int a, int b, int c) {
    int dp[n + 10];
    
    for (int i = 0; i < n + 10; i++) {
        dp[i] = -1;
    }
    
    dp[0] = 0;
    
    for (int i = 0; i <= n; i++) {
        if (dp[i] == -1) {
            continue;
        }
        
        if (i + a <= n) {
            if (dp[i] + 1 > dp[i + a]) {
                dp[i + a] = dp[i] + 1;
            } else {
                dp[i + a] = dp[i + a];
            }
        }
        
        if (i + b <= n) {
            if (dp[i] + 1 > dp[i + b]) {
                dp[i + b] = dp[i] + 1;
            } else {
                dp[i + b] = dp[i + b];
            }
        }
        
        if (i + c <= n) {
            if (dp[i] + 1 > dp[i + c]) {
                dp[i + c] = dp[i] + 1;
            } else {
                dp[i + c] = dp[i + c];
            }
        }
    }
    
    return dp[n];
}