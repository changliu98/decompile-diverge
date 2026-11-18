int func0(int *nums, int numsSize) {
    int max = 0;
    int i = 0;
    while (i < numsSize) {
        if (nums[i] > 0) {
            int sum = -nums[i] + func0(nums + i + 1, numsSize - i - 1);
            max += sum;
            i += sum - 1;
        } else {
            max += nums[i];
        }
        i++;
    }
    return max;
}