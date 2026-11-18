int sumEven(int *nums, int numsSize) {
    int sum = 0;
    int i = 0;
    while (1) {
        if (i >= numsSize) break;
        if (nums[i] % 2 == 0) sum += nums[i];
        i += 2;
    }
    return sum;
}