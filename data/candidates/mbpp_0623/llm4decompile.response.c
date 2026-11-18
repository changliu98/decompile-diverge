void func0(int *nums, int length, int n, int *result)
{
    for (int i = 0; i < length; i++)
    {
        result[i] = (int)pow((double)nums[i], (double)n);
    }
}