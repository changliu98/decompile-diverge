int func0(int *a, int k, int p)
{
    int i;
    int coord_hash = 1;

    for (i = 0; ; )
    {
        if (i >= k)
            break;

        coord_hash = (coord_hash * (a[i] % p)) % p;
        i++;
    }

    return coord_hash % p;
}