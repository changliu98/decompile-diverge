int func0(int *nums, int numsSize) {
    int dp[numsSize];
    int i, j, k;
    for (i = 0; i < numsSize; i++) {
        dp[i] = 1;
    }
    for (i = 1; i < numsSize; i++) {
        for (j = 0; j < i; j++) {
            if (nums[i] > nums[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }
    int max = 0;
    for (k = 0; k < numsSize; k++) {
        if (dp[k] > max) {
            max = dp[k];
        }
    }
    return max;
}