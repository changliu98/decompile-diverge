int func0(const char *str) {
    int length = strlen(str);
    int n = length;
    
    // Allocate a 2D VLA (Variable Length Array) of size n x n
    int dp[n][n];
    
    // Initialize the diagonal (substrings of length 1)
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    // Check substrings of length 2 to n
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            
            if (str[i] == str[j]) {
                if (len == 2) {
                    dp[i][j] = 2;
                } else {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
            } else {
                if (dp[i][j - 1] > dp[i + 1][j]) {
                    dp[i][j] = dp[i][j - 1];
                } else {
                    dp[i][j] = dp[i + 1][j];
                }
            }
        }
    }
    
    return dp[0][n - 1];
}