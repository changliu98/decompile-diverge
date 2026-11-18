define GPS_EPOCH_TO_MJD 44244

void __cdecl sun_gpstime2mjulianday(int week, double tow, long *daynum)
{
  // Calculate the number of full days from the time of week (tow)
  // The (int) cast truncates towards zero, and (unsigned int) ensures 
  // standard modulo-like positive conversion behavior in 32-bit arithmetic.
  int days_from_tow = (int)(tow / SECONDS_IN_WEEK);
  
  // Calculate the total days: 
  // 1. Days from the current week's time
  // 2. Days from the GPS week number (7 days per week)
  // 3. The Modified Julian Date (MJD) offset for the GPS epoch (Jan 6, 1980)
  *daynum = (unsigned int)days_from_tow + (__int64)(7 * week) + GPS_EPOCH_TO_MJD;
}