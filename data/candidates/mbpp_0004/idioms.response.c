void func0(int *num, int size, int n, int *min)
{
    int i = 0;
    qsort(num,size,sizeof(int),compare);
    for(i=0;i<n;i++)
    {
        min[i]=num[i];
    }
    return;
}