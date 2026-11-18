void cal_to_jul(int year, int *month, int *day)
{
    int a, b, c, d, e, f, m, n;

    a = year % 4;
    b = year % 7;
    c = year % 19;
    d = (15 + 19 * c) % 30;
    e = (2 + 2 * a + 4 * b - d) % 7;
    f = (d + e + 114) / 31;
    m = (d + e + 114) % 31;

    *month = f;
    *day = m + 1;
}