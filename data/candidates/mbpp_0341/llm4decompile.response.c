void func0(int *arr, int n, int *result)
{
    qsort(arr, (size_t)n, sizeof(int), cmpfunc);
    int i;
    for (i = 0; i < n; i++)
        result[i] = arr[i];
}