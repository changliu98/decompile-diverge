void get_sum(int *nums, int size, int *sum)
{
    int i;
    for (i = 0; i < size - 1; i++)
        sum[i] = nums[i] + nums[i + 1];
}