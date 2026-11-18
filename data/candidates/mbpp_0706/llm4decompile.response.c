bool func0(int *arr1, int m, int *arr2, int n)
{
    bool hashset[1000];
    memset(hashset, 0, 1000);
    for (int i = 0; i < m; i++)
    {
        hashset[arr1[i]] = true;
    }
    for (int i = 0; i < n; i++)
    {
        if (!hashset[arr2[i]])
        {
            return false;
        }
    }
    return true;
}