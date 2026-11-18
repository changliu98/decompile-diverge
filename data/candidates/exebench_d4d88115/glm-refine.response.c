void __cdecl gsdate(int day, int mon, int year, int *serial)
{
  int yeara; 
  int mona; 

  // Adjust the year and month for the Julian Day algorithm.
  // The algorithm treats March as the first month of the year, 
  // and January/February as the last months of the *previous* year.
  if ( mon <= 2 )
  {
    mona = mon + 9;   // Jan -> 10, Feb -> 11
    yeara = year + 99; // Shift year back by 1 (relative to the +100 base)
  }
  else
  {
    mona = mon - 3;   // Mar -> 0, Apr -> 1, etc.
    yeara = year + 100; // Base year shift
  }

  // Calculate the serial date.
  // (153 * mona + 2) / 5 computes the cumulative days of the preceding months.
  // 1461 * yeara / 4 accounts for the days in previous years, including leap years.
  // The constant 36466 is the epoch offset (days before March 1st of the base year 1900).
  int i = day + (153 * mona + 2) / 5 + 1461 * yeara / 4 - 36466;

  // Adjust for leap year discrepancy.
  // If the date is after February 28th (serial > 59), the offset is adjusted by 1 day.
  // This likely corrects an off-by-one error in the original implementation regarding 
  // leap day accounting for the epoch base year.
  if ( i > 59 )
  {
    i = day + (153 * mona + 2) / 5 + 1461 * yeara / 4 - 36467;
  }

  *serial = i;
}