int func0(const char *s) {
    int len = strlen(s);
    int n = len + 1;
    int dp[n][n];
    
    for (int i = 0; i <= len; i++) {
        for (int j = 0; j <= len; j++) {
            dp[i][j] = 0;
        }
    }
    
    for (int i = 1; i <= len; i++) {
        for (int j = 1; j <= len; j++) {
            if (s[i - 1] == s[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    
    return dp[len][len];
}