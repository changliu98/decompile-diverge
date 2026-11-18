int func0(int *nums, int numsSize) {
    int i = 0, j = 0;
    int max;
    while (i < numsSize - 1) {
        while (j < numsSize - i - 1) {
            if (nums[j] > nums[j + 1]) {
                int tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            } else {
                j++;
            }
        }
        i++;
        j = 0;
    }
    max = INT_MAX;
    i = 0;
    while (i < numsSize - 1) {
        if (nums[i + 1] - nums[i] < max) {
            max = nums[i + 1] - nums[i];
        }
        i++;
    }
    return max;
}