void __cdecl easterj(int year, int *month, int *day)
{
    // 'a' represents the lunar cycle correction (often related to the Golden Number)
    int a = (19 * (year % 19) + 15) % 30;

    // 'e' represents the weekly correction (finding the Sunday)
    int e = (4 * (year % 7) + 2 * (year % 4) - a + 34) % 7;

    // Total days after March 1st (March = month 3, so 114 = 31 * 3 + 21)
    int total_days = e + a + 114;

    *month = total_days / 31;
    *day = (total_days % 31) + 1;
}