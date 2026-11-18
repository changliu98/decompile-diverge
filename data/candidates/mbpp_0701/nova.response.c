int func0(int *nums, int numsSize) {
    int sum = 0;
    int i = 0;
    while (i < numsSize) {
        sum += nums[i];
        i++;
    }
    int leftsum = 0;
    int j = 0;
    while (j < numsSize) {
        sum -= nums[j];
        if (leftsum == sum) {
            return j;
        }
        leftsum += nums[j];
        j++;
    }
    return -1;
}