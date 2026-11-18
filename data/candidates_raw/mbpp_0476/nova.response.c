int func0(int *nums, int numsSize) {
    int max = INT_MIN;
    int min = INT_MAX;
    int i = 0;
    while (1) {
        if (i >= numsSize) {
            break;
        }
        if (nums[i] > max) {
            max = nums[i];
        }
        if (nums[i] < min) {
            min = nums[i];
        }
        i++;
    }
    return max + min;
}