void __cdecl j2gcal(int *y, int *m, int *d, double j)
{
    // Calculate the Julian Day Number (rounded to the nearest integer)
    int jdn = (int)(j + 0.5);
    int l = jdn + 68569;

    // Calculate the 400-year cycle (n) and the 100-year cycle (i)
    int n = 4 * l / 146097;
    int l2 = l - (146097 * n + 3) / 4;

    int i = 4000 * (l2 + 1) / 1461001;
    int l3 = l2 - (1461 * i / 4 - 31);

    // Calculate the day of the year and derive the month (x)
    int x = 80 * l3 / 2447;

    // Calculate the final Day, Month, and Year
    *d = l3 - 2447 * x / 80;
    *m = x + 2 - 12 * (x / 11);
    *y = 100 * (n - 49) + i + x / 11;
}