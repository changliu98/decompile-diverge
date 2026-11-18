int func0(int *arr, int n) {
    int dp[n];
    
    if (n >= 1) {
        dp[0] = arr[0];
    }
    if (n >= 2) {
        dp[1] = arr[0] + arr[1];
    }
    if (n > 2) {
        int val1 = (dp[1] > arr[1] + arr[2]) ? dp[1] : arr[1] + arr[2];
        dp[2] = (val1 > arr[0] + arr[2]) ? val1 : arr[0] + arr[2];
    }
    
    for (int i = 3; i < n; i++) {
        int prev1 = dp[i - 1];
        int prev2 = dp[i - 2] + arr[i];
        int prev3 = arr[i] + arr[i - 1] + dp[i - 3];
        
        int max1 = (prev1 > prev2) ? prev1 : prev2;
        int max2 = (prev1 > prev2) ? prev1 : prev2;
        
        dp[i] = (max2 > prev3) ? max2 : prev3;
    }
    
    return dp[n - 1];
}