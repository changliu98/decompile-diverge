int func0(int *nums, int numsSize) {
    int i, j, k, count = 0;
    for (i = 0;; i++) {
        if (i >= numsSize)
            break;
        if (nums[i] < 0)
            count++;
        else
            continue;
    }
    return count;
}