int *func0(int *nums, int numsSize) {
    int max = 0;
    int i = 0;
    while (i < numsSize) {
        if (nums[i] > max) {
            max = nums[i];
        }
        i++;
    }
    int *bucket = (int *)malloc((max + 1) * sizeof(int));
    int j = 0;
    while (j <= max) {
        bucket[j] = 0;
        j++;
    }
    int k = 0;
    while (k < numsSize) {
        if (bucket[nums[k]] < bucket[k]) {
            nums[k] = k;
            k++;
        } else {
            bucket[nums[k]]++;
            k++;
        }
    }
    return bucket;
}