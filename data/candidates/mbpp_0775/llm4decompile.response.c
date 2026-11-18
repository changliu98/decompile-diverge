bool func0(int *nums, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (nums[i] % 2 != i % 2)
        {
            return false;
        }
    }
    return true;
}