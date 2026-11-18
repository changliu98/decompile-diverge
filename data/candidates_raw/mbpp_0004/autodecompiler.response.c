void sort(int *a, int n, int m, int *b)
{
    int i;
    qsort(a,n,sizeof(int),compare);
    for(i=0;i<m;i++)
    {
        b[i]=a[i];
    }
}