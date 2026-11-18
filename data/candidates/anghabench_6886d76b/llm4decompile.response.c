int ilog2(size_t n)
{
    int i;
    for (i = 0; (1UL << i) < n; i++) ;
    return i;
}