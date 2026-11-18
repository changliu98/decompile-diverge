int func0(int *nums, int numsSize, int target) {
    int i = 0;
    int j = 0;
    for (;;) {
        if (j < numsSize) {
            if (nums[j] == target) {
                i++;
            }
            j++;
        } else {
            break;
        }
    }
    return i;
}