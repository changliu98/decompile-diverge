int func0(int *nums, int size)
{
    int i;
    int max_num;
    int min_num;

    max_num = -2147483648;
    min_num = 2147483647;

    for (i = 0; i < size; i++)
    {
        if (nums[i] > max_num)
        {
            max_num = nums[i];
        }

        if (nums[i] < min_num)
        {
            min_num = nums[i];
        }
    }

    return max_num + min_num;
}