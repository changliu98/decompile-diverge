int func0(int *nums, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (nums[i] % 2 != 0) {
            return nums[i];
        }
    }
    return -1;
}