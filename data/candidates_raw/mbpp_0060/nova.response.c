int func0(int *nums, int numsSize) {
    int *dp = (int *)malloc(sizeof(int) * numsSize);
    int max = 0;
    for (int i = 0; i < numsSize; i++) {
        dp[i] = 1;
    }
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (abs(nums[i] - nums[j]) <= 1) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
    }
    for (int i = 0; i < numsSize; i++) {
        if (max < dp[i]) {
            max = dp[i];
        }
    }
    free(dp);
    return max;
}