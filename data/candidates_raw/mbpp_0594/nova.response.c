int func0(int *nums, int numsSize) {
    int i, j;
    int a = -1, b = -1;
    for (i = 0;; i++) {
        if (i >= numsSize)
            break;
        if (nums[i] % 2 == 0) {
            a = nums[i];
        } else {
            continue;
        }
    }
    for (j = 0;; j++) {
        if (j >= numsSize)
            break;
        if (nums[j] % 2!= 0) {
            b = nums[j];
        } else {
            continue;
        }
    }
    return a - b;
}