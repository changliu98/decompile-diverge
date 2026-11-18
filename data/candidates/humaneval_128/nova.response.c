int func0(int *nums, int numsSize) {
    if (numsSize == 0) {
        return -2147483648;
    }

    int sum = 0;
    int max = 1;
    int i = 0;
    int sign = 0;
    while (i < numsSize) {
        sum += abs(nums[i]);
        if (nums[i] == 0) {
            sign = 0;
        }
        if (nums[i] < 0) {
            sign = -sign;
        }
        i++;
    }
    max *= sum;
    max *= sign;
    return max;
}