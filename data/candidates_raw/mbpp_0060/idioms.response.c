int LIS(int *array, int n)
{
    int *mls = (int *)malloc(n*sizeof(int));
    int i; int j; int k;
    int max = 0;
    for(i = 0; i < n; i++)
        mls[i] = 1;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < i; j++)
        {
            if(abs(array[i]-array[j]) <= 1 && mls[i] < mls[j]+1)
                mls[i] = mls[j]+1;
        }
    }
    for(i = 0; i < n; i++)
    {
        if(max < mls[i])
            max = mls[i];
    }
    free(mls);
    return max;
}