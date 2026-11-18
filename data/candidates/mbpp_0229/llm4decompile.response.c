int func0(int *arr1, int *arr2, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (arr1[i] != arr2[i])
            return 0;
    }
    return 1;
}