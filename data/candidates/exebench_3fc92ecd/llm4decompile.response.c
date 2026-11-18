void julian_to_date(long jd, int *y, int *m, int *d)
{
    long x, z, l, n, i, j, k;

    l = jd + 68569;
    n = 4 * l / 1461;
    x = l - (1461 * n + 3) / 4;
    i = 4000 * (x + 1) / 1461001;
    x -= 1461 * i / 4;
    j = 4800 * x / 146097;
    k = x - 1461 * j / 4;

    *d = (int) (k);
    *m = (int) ((j + 11) % 12 + 1);
    *y = (int) (40 * (n - 49) + i - 4800 + j / 12);
}