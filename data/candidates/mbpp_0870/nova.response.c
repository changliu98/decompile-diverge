int func0(int *nums, int numsSize) {
    int i, sum = 0;
    for (i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            sum += nums[i];
        } else {
            i++;
        }
    }
    return sum;
}