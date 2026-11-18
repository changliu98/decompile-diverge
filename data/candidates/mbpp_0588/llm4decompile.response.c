int func0(int *nums, int size)
{
    int i;
    int max_val = -2147483648;
    int min_val = 2147483647;

    for (i = 0; i < size; i++)
    {
        if (nums[i] > max_val)
        {
            max_val = nums[i];
        }
        if (nums[i] < min_val)
        {
            min_val = nums[i];
        }
    }

    return max_val - min_val;
}