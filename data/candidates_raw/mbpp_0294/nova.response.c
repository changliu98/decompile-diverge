int func0(int *nums, int numsSize) {
    int max = INT_MIN;
    int i = 0;
    while (1) {
        if (i >= numsSize) {
            break;
        }
        if (nums[i] > max) {
            max = nums[i];
        }
        i++;
    }
    return max;
}