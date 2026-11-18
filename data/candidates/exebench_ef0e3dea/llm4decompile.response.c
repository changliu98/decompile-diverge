void sun_mjulianday2date(long mjd, int *year, int *month, int *day)
{
    long jd;
    int l, n;

    jd = (long)(mjd + 2400001);

    l = jd + 68569;
    n = 4 * l / 1461;
    l = l % 1461;

    *year = 4 * n / 1461;
    l = l % 1461 / 4;

    *month = 5 * l / 153;
    *day = l % 153 / 5 + 1;

    *year += *month / 12;
    *month = (*month % 12) + 1;

    *year -= 4716;

    if (*year <= 0)
        *year -= 1;

    return;
}