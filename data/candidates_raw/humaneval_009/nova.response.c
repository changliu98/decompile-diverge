int *func0(int *nums, int numsSize) {
    if (numsSize < 1) {
        return NULL;
    }

    int *result = (int *)malloc(sizeof(int) * numsSize);
    if (result == NULL) {
        return NULL;
    }

    int max = nums[0];
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
        result[i] = max;
    }

    return result;
}