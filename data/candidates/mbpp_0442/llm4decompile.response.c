double func0(int *nums, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        if (nums[i] > 0)
            count++;
    return round((double)count / n * 100) / 100;
}