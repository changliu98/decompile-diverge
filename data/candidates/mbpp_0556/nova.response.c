int func0(int *nums, int numsSize) {
    int i, j, k;
    int count = 0;
    for (i = 0; i < numsSize; i++) {
        for (j = i + 1; j < numsSize; j++) {
            if ((nums[i] ^ nums[j]) % 3 == 0) {
                count++;
            }
        }
    }
    return count;
}