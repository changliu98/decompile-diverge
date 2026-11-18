int func0(int *nums, int size)
{
    int i;
    int sum = 0;
    for (i = 0; i < size; i++)
        sum = sum * 10 + nums[i];
    return sum;
}