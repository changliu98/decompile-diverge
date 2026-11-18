int func0(int *nums, int numsSize) {
    int i, j, k, max;
    int dp[numsSize];
    for (i = 0; i < numsSize; i++) {
        dp[i] = 1;
    }
    for (i = 0; i < numsSize; i++) {
        for (j = 0; j < i; j++) {
            if (nums[i] == nums[j] + 1 || nums[i] == nums[j] - 1) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
    }
    max = 1;
    for (k = 0; k < numsSize; k++) {
        if (dp[k] < max) {
            max = dp[k];
        }
    }
    return max;
}