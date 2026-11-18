int constrainedSubsetSum(int *nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), &cmpfunc);

    int *dp = (int *)malloc(numsSize * sizeof(int));
    dp[0] = 0;
    int i;
    for (i = 1; ; i++) {
        if (i >= numsSize)
            break;

        dp[i] = dp[i - 1];
        if (nums[i] - nums[i - 1] < k) {
            int t;
            if (i >= 3) {
                if (dp[i] > nums[i] + dp[i - 2] + nums[i - 1]) {
                    t = dp[i];
                } else {
                    t = nums[i] + dp[i - 2] + nums[i - 1];
                }
            } else {
                if (dp[i] > nums[i] + nums[i - 1]) {
                    t = dp[i];
                } else {
                    t = nums[i] + nums[i - 1];
                }
            }
            dp[i] = t;
        }
    }

    int ret = dp[numsSize - 1];
    free(dp);
    return ret;
}