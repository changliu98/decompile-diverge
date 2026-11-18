void cal2greg(int year, int *month, int *day)
{
    int j, k, l, n, i, m, d, y;

    j = year % 19;
    k = year / 100;
    l = year % 100;
    n = k / 4;
    i = k % 4;
    m = (k + 8) / 25;
    d = (k - m + 1) / 3;
    y = (19 * j + k - n - d + 15) % 30;
    h = (l / 4);
    g = (l % 4);
    f = (i * 2 + 32 + h * 2 - y - g) % 7;
    e = (j + 11 * y + 22 * f) / 451;
    m = (y + f - 7 * e + 114) / 31;
    n = ((y + f - 7 * e + 114) % 31) + 1;

    *month = m;
    *day = n;
}