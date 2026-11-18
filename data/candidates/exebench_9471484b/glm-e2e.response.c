void SdnToGregorian(int64_t sdn, int *year, int *month, int *day) {
    int dyear;
    int dmonth;
    int dday;
    int64_t temp;
    int64_t julianDay;

    if (sdn <= 0 || sdn > 0x1fffffffffff82d2) {
        *year = 0;
        *month = 0;
        *day = 0;
        return;
    }

    // Calculate the Julian Day Number
    julianDay = (sdn + 32045) * 4 - 1;

    // Calculate the year
    dyear = (int)(julianDay / 146097);

    // Adjust julianDay
    julianDay = ((julianDay % 146097) / 4) * 4 + 3;

    // Calculate intermediate values for month and day
    int64_t temp2 = (int64_t)dyear * 100;
    dmonth = (int)(temp2 + (julianDay / 1461));
    julianDay = ((julianDay % 1461) / 4) * 5 - 3;

    // Calculate the day of the year
    dday = (int)(julianDay / 153);
    int day_of_month = (int)((julianDay % 153) / 5) + 1;

    // Adjust month and year
    if (dmonth < 10) {
        dmonth += 3;
    } else {
        dmonth -= 9;
        dyear++;
    }

    // Adjust year to the Gregorian calendar
    dyear -= 4800;
    if (dyear <= 0) {
        dyear--;
    }

    *year = dyear;
    *month = dmonth;
    *day = day_of_month;
}