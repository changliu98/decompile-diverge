int func0(int *a, int l, int u)
{
    int m, ret;
    if (l > u)
        ret = l;
    else {
        m = l + (u-l)/2;
        if (a[m] == m)
            ret = func0(a, m+1, u);
        else
            ret = func0(a, l, m-1);
    }
    return ret;
}