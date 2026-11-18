int lis(int a[], int n)
{
    int *l = (int*) (a - ( ( (sizeof(int)) * (n) + sizeof(int) - 1 ) & ~(sizeof(int) - 1 ) ));
    int i; int j;
    for (i = 0 ; i < n ; i++)
        l[i] = 1;
    for (i = 1 ; i < n ; i++)
        for (j = 0 ; j < i ; j++)
            if (a[i] > a[j] && l[i] < l[j]+1)
                l[i] = l[j]+1;
    int max = 0;
    for (i = 0 ; i < n ; i++)
        if (l[i] > max)
            max = l[i];
    return max;
}