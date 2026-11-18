void __cdecl julian_to_date(long jd, int *y, int *m, int *d)
{
    long n, i, j;
    long a, b, c, e, f;

    // Offset the Julian Day Number to align with the algorithm's epoch
    a = jd + 68569;

    // Calculate the 400-year cycle (n) and the remaining days
    n = 4 * a / 146097;
    a -= (146097 * n + 3) / 4;

    // Calculate the 100-year cycle (i) within the 400-year cycle
    i = 4000 * (a + 1) / 1461001;
    a -= 1461 * i / 4;

    // Calculate the month (j is a temporary value representing the month offset)
    b = a + 31;
    j = 80 * b / 2447;

    // Calculate the day of the month
    c = b - 2447 * j / 80;
    *d = c;

    // Calculate the month (adjusting for the calendar year starting in March)
    *m = j + 2 - 12 * (j / 11);

    // Calculate the full year
    *y = j / 11 + i + 100 * (n - 49);
}