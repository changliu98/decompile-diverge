_Bool isSubset(int a[], int m, int b[], int n)
{
    int i; int j;
    int hashset[1000];
    memset(hashset, 0, sizeof(hashset));
    for (i = 0; i < m; i++)
        hashset[a[i]] = 1;
    for (j = 0; j < n; j++)
        if (hashset[b[j]] == 0)
            return 0;
    return 1;
}