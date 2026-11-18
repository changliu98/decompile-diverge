void __cdecl easterg(int year, int *month, int *day)
{
    int a = year % 19;             // Golden number - 1
    int b = year / 100;            // Century
    int c = year % 100;            // Year of the century

    int d = b / 4;                 // Number of leap years since year 0
    int e = b % 4;                 // Solar correction
    int f = (b + 8) / 25;          // Moon's orbit correction
    int g = (b - f + 1) / 3;       // Lunar correction

    // h is the number of days from March 21st until the Paschal full moon
    int h = (19 * a + b - d - g + 15) % 30;

    int i = c / 4;                 // Number of leap years in the current century
    int k = c % 4;                 // Year's position in the leap year cycle

    // l is the number of days from the Paschal full moon to the Sunday after
    int l = (2 * e + 2 * i - h + 32 - k) % 7;

    // m is the correcting factor for the Paschal full moon falling on a Sunday
    int m = (22 * l + 11 * h) / 451;

    // Total number of days from March 1st to Easter Sunday
    int n = l + h - 7 * m + 114;

    *month = n / 31;               // Month (3 = March, 4 = April)
    *day = (n % 31) + 1;           // Day of the month
}