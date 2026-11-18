int func0(int *nums, int numsSize) {
    int i, j, sum = 0;
    for (i = 0;; i++) {
        for (j = i + 1; j < numsSize; j++) {
            sum += nums[i] ^ nums[j];
        }
    }
    return sum;
}