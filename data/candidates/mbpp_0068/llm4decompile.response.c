int func0(int *A, int n)
{
    int i;
    int flag1 = 1;
    int flag2 = 1;
    for (i = 0; i < n - 1; i++)
    {
        if (A[i] > A[i + 1])
            flag1 = 0;
        if (A[i] < A[i + 1])
            flag2 = 0;
    }
    if (flag1 || flag2)
        return 1;
    return 0;
}