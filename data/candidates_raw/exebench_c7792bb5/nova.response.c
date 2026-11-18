static void func0(int year, int *month, int *day)
{
    int ndays, nleap, n100, n400;
    int m, d;

    ndays = year % 19;
    nleap = year % 4;
    n100  = year % 100;
    n400  = year % 400;

    m = (19 * ndays +  9) / 25;
    d = (ndays + m + 1  + 7) % 30;
    m = (m + 2) % 12;
    d = (d + m * 22 + 4) % 7;
    ndays = d + d + m * 11 + 114;
    *month = (ndays + 7) / 31;
    *day = (ndays + d) % 31 + 1;
}