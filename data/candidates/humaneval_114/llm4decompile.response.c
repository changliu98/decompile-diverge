long long func0(long long *nums, int size)
{
    long long min = nums[0];
    long long current = nums[0];
    for (int i = 1; i < size; i++) {
        if (current < 0) {
            current = current + nums[i];
        } else {
            current = nums[i];
        }
        if (current < min) {
            min = current;
        }
    }
    return min;
}