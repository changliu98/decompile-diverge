bool func0(int *nums, int numsSize) {
    bool dp[numsSize];
    int i, j, k;
    bool flag;
    dp[0] = true;
    for (i = 0, j = 0; i < numsSize;) {
        int step = nums[i];
        flag = false;
        for (k = 0; k < j; k++) {
            if (dp[k] && k + step == i) {
                flag = true;
                break;
            }
        }
        if (flag) {
            dp[i + 1] = true;
        } else {
            dp[i + 1] = false;
        }
        i++;
    }
    return dp[numsSize];
}