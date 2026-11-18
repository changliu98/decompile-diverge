int func0(int *nums, int numsSize, int target) {
    if (target == 0) {
        return 0;
    }
    int min = INT_MAX;
    int i = 0;
    while (i < numsSize) {
        if (nums[i] <= target) {
            int sub = func0(nums, numsSize, target - nums[i]);
            if (sub!= INT_MAX && sub + 1 < min) {
                min = sub + 1;
            }
        }
        i++;
    }
    return min;
}