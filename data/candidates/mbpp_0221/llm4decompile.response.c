int func0(int *nums, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (nums[i] % 2 == 0)
        {
            return nums[i];
        }
    }
    return -1;
}