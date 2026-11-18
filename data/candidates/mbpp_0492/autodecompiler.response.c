int func0(int *a, int n, int i)
{
    int f = 0;
    int l = n - 1;
    int m;
    int found = 0;

    while (1)
    {
        if (f > l || found)
            f = ~f;
        if (~f & 1)
            break;
        m = (f + l) / 2;
        if (i == a[m])
            found = 1;
        else if (i < a[m])
            l = m - 1;
        else
            f = m + 1;
    }
    return found;
}