int func0(int *nums, int numsSize) {
    int i, j, max, tmp;
    int dp[numsSize];

    if (numsSize == 0 || nums[0] == 0) {
        max = INT_MAX;
        i = 1;
    } else {
        dp[0] = 0;
        for (i = 1; i < numsSize; i++) {
            dp[i] = INT_MAX;
            for (j = 0; j < i; j++) {
                if (j + nums[j] >= i && dp[j]!= INT_MAX) {
                    if (dp[i] > dp[j] + 1) {
                        tmp = dp[i];
                    } else {
                        tmp = dp[j] + 1;
                    }
                    dp[i] = tmp;
                    break;
                }
            }
        }
        max = dp[numsSize - 1];
        i = 1;
    }

    return max;
}