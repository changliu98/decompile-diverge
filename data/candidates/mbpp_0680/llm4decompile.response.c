bool func0(int *nums, int size)
{
    int i;
    for (i = 0; i < size - 1; i++)
    {
        if (nums[i] > nums[i + 1])
            return false;
    }
    return true;
}