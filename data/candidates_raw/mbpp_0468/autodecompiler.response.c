int maxProduct(int* nums, int numsSize) {
    int dp[numsSize];
    for (int i = 0; i < numsSize; ++i)
        dp[i] = nums[i];
    int i, j;
    for (i = 1; i < numsSize; ++i) {
        for (j = 0; j < i; ++j) {
            if (nums[j] < nums[i] && dp[j]*nums[i] > dp[i])
                dp[i] = dp[j]*nums[i];
        }
    }
    int max = dp[0];
    for (i = 1; i < numsSize; ++i) {
        if (dp[i] > max)
            max = dp[i];
    }
    return max;
}