int func0(int *nums, int numsSize, int target) {
    int i = 0, j = 0, count = 0;
    while (j < numsSize) {
        for (i = j + 1; i < numsSize; i++) {
            if (nums[j] - nums[i] == target || nums[i] - nums[j] == target) {
                count++;
            }
        }
        j++;
    }
    return count;
}