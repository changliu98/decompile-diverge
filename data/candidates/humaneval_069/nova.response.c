int func0(int *nums, int numsSize) {
    int *count = (int *)calloc(numsSize + 1, sizeof(int));
    int max = -1;
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
        if (count[nums[i]] >= nums[i] && nums[i] > max) {
            max = nums[i];
        }
    }
    free(count);
    return max;
}