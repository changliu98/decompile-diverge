int func0(int *nums, int numsSize) {
    int min = INT_MIN;
    int max = INT_MAX;
    int i = 0;
    while (i < numsSize) {
        if (nums[i] > min)
            min = nums[i];
        if (nums[i] < max)
            max = nums[i];
        i++;
    }
    return min - max;
}