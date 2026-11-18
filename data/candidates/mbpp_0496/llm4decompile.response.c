void func0(int *nums, int len, int n, int *result)
{
    qsort(nums, (size_t)len, sizeof(int), compare);
    for (int i = 0; i < n; i++)
        result[i] = nums[i];
}