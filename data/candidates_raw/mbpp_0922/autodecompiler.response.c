void max_product(int *nums, int numsSize, int *first, int *second) {
    if (numsSize < 3) {
        *first = 0;
        *second = 0;
        return;
    }
    *first = nums[0];
    *second = nums[1];
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] * nums[j] > *first * *second) {
                *first = nums[i];
                *second = nums[j];
            }
        }
    }
}