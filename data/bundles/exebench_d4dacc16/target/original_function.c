void findMinMax(long int *nums, long int *min, long int *max) {
    for (int i = 1; i < 5; i++) {
        if (nums[i] < *min) {
            *min = nums[i];
        }
        if (nums[i] > *max) {
            *max = nums[i];
        }
    }
    return;
}