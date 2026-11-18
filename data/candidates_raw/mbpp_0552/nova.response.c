char *func0(int *nums, int numsSize) {
    int i, j;
    int *diff = (int *)malloc(sizeof(int) * (numsSize - 1));
    for (i = 1; i < numsSize; i++) {
        diff[i - 1] = nums[i] - nums[i - 1];
    }
    for (j = 1; j < numsSize - 1; j++) {
        if (diff[j]!= diff[0]) {
            char *ret = "NO";
            i = 1;
            break;
        }
    }
    if (i == numsSize - 1) {
        char *ret = "YES";
        i = 1;
    }
    return ret;
}