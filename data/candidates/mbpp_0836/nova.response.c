int func0(int *nums, int numsSize) {
    int max = INT_MIN;
    int sum = 0;
    int start = 0;
    int end = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < numsSize; i++) {
        sum += nums[i];
        if (max < sum) {
            max = sum;
            start = j;
            end = i;
        }
        if (sum < 0) {
            sum = 0;
            j = i + 1;
        }
    }
    return end - start + 1;
}