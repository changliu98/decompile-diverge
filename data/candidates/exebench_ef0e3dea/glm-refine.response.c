void __cdecl sun_mjulianday2date(long daynum, int *year, int *month, int *day)
{
    // Step 1: Convert Modified Julian Day (MJD) to Julian Day (JD)
    // JD = daynum + 2400001
    long jd = daynum + 2400001;

    // Step 2: Calculate the number of 400-year cycles (Gregorian calendar)
    // (4 * jd + 274277) / 146097
    long c = (4 * jd + 274277) / 146097;

    // Step 3: Calculate the number of days within the current 400-year cycle
    // d = jd + 2401402 - 38 - (3 * c / 4)
    long d = jd + 2401364 - (3 * c / 4);

    // Step 4: Calculate the number of 4-year cycles (Julian years)
    long b = (4 * d + 3) / 1461;

    // Step 5: Calculate the day of the year (0-indexed)
    // h = 5 * ((4 * d + 3) % 1461 / 4) + 2
    long h = 5 * ((d - 1461 * b) / 4) + 2;

    // Step 6: Extract the day, month, and year from the intermediate values
    *day   = (h % 153) / 5 + 1;
    *month = (h / 153 + 2) % 12 + 1;
    *year  = (14 - *month) / 12 + b - 4716;
}