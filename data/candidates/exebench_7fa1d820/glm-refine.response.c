void __cdecl SdnToJulian(long sdn, int *pYear, int *pMonth, int *pDay)
{
    // 0x1FFFFFFFFFFF82ADLL is the maximum valid SDN for a 32-bit Julian year
    if (sdn > 0 && sdn <= 0x1FFFFFFFFFFF82ADLL)
    {
        // Calculate the Julian year and the day within that year.
        // The offset 128331 aligns the cycle so that leap years are the 4th year.
        int year = (int)((4 * sdn + 128331) / 1461);
        int dayOfYear = (int)((4 * sdn + 128331) % 1461) / 4 + 1;

        // Check for 32-bit signed integer overflow/underflow
        if (year > 0x7FFFFFFF || year < (int)0x80000000)
        {
            *pYear = 0;
            *pMonth = 0;
            *pDay = 0;
            return;
        }

        // Determine the month. The Julian calendar is treated as starting in March.
        // The formula (5 * dayOfYear - 3) / 153 maps days 1-153 to months 0-4.
        int month = (5 * dayOfYear - 3) / 153;
        
        if (month >= 10)
        {
            // Months 10 and 11 correspond to January and February of the next year.
            year++;
            month -= 9;
        }
        else
        {
            // Shift the 0-based month index to match the standard calendar.
            month += 3;
        }

        // Convert to astronomical year numbering (1 BC = Year 0, 2 BC = Year -1, etc.)
        year -= 4800;
        if (year <= 0)
            year--;

        *pYear = year;
        *pMonth = month;
        *pDay = (5 * dayOfYear - 3) % 153 / 5 + 1;
    }
    else
    {
        *pYear = 0;
        *pMonth = 0;
        *pDay = 0;
    }
}