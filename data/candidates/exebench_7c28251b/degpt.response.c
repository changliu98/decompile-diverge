// Converts GPS week and Time of Week (TOW) to Modified Julian Day number.
// Parameters:
//   week: GPS week number.
//   tow: Time of Week in seconds.
//   daynum: Output pointer to store the calculated Modified Julian Day number.
void sun_gpstime2mjulianday(int gps_week, double time_of_week, long *modified_julian_day)
{
    // Calculate the Modified Julian Day number by converting the GPS week to days,
    // adding the days from the Time of Week, and applying the GPS epoch offset.
    *modified_julian_day = (long)(gps_week * 7) + (long)(time_of_week / SECONDS_PER_WEEK) + 0xacd4;
}