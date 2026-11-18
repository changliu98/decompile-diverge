int func0(int *nums, int numsSize) {
    if (numsSize < 3) {
        return -1;
    }
    int max1 = INT_MAX;
    int max2 = INT_MAX;
    int index = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < max1) {
            max2 = max1;
            max1 = nums[i];
        } else if (nums[i] < max2 && nums[i]!= max1) {
            max2 = nums[i];
        } else {
            continue;
        }
    }
    if (max2 == INT_MAX) {
        return -1;
    }
    return max2;
}