int func0(int *nums, int numsSize, int target) {
    int i = 0, j = 0;
    while (j < numsSize) {
        if (nums[j] == target) {
            i++;
        } else {
            j++;
        }
    }
    return i;
}