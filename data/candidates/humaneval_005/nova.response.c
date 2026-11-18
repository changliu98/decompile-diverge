int *func0(int *nums, int numsSize, int n, int *returnSize) {
    int *ret;
    int i, j;
    *returnSize = numsSize > 0? 2 * numsSize - 1 : 0;
    ret = (int *)malloc(sizeof(int) * (*returnSize));
    for (i = 0, j = 0; i < numsSize; i++) {
        ret[j++] = n;
        ret[j++] = nums[i];
    }
    return ret;
}