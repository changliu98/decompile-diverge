void __cdecl sun_mjulianday_to_date(unsigned int mjd, int *year, int *month, int *day)
{
  int b; // Number of 400-year leap cycles
  int d; // Number of 4-year periods within the current 400-year cycle
  int m; // Number of 5-month periods within the current 4-year period
  
  // JD is the Julian Day number. MJD 0 corresponds to JD 2400000.5.
  // The constant 2432045 aligns the epoch to the start of a 400-year cycle 
  // (specifically, March 1, 0 AD in the proleptic Gregorian calendar).
  int jd = mjd + 2432045;

  // Determine the 400-year cycle count.
  // 146097 is the number of days in 400 Gregorian years (365 * 400 + 97 leap days).
  // The +3 offset ensures correct floor division for negative values.
  b = (int)(4 * jd + 3) / 146097;

  // Determine the 4-year cycle count within the 400-year cycle.
  // 1461 is the number of days in 4 years (365 * 4 + 1 leap day).
  d = (int)(4 * (jd - 146097 * b / 4) + 3) / 1461;

  // Determine the 5-month block within the 4-year cycle.
  // 153 is the number of days in 5 months (31 + 30 + 31 + 30 + 31).
  m = (int)(5 * (jd - 146097 * b / 4 - 1461 * d / 4) + 2) / 153;

  // Calculate the day of the month.
  *day = jd - 146097 * b / 4 - 1461 * d / 4 - (153 * m + 2) / 5 + 1;

  // Calculate the month. The algorithm treats March as the first month of the 
  // year (m=0), so we add 3. If m >= 10 (January or February), we subtract 12 
  // and effectively push the year back by 1.
  *month = m + 3 - 12 * (m / 10);

  // Calculate the year.
  // m / 10 adds 1 if the month is January or February.
  // 100 * b accounts for the 400-year cycles.
  // 4800 aligns the epoch (since year 0 is treated as year 4800 in this formula).
  *year = m / 10 + d + 100 * b - 4800;
}