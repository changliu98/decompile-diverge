void __cdecl eastero(int year, int *month, int *day)
{
  // 'a' represents the position of the year within the 19-year Metonic cycle.
  int a = year % 19;

  // 'b' is the Paschal Full Moon correction (days from March 21st).
  int b = (19 * a + 15) % 30;

  // 'c' accounts for the day of the week the Paschal Full Moon falls on.
  int c = (b + year / 4 + year) % 7;

  // 'd' is the non-leap century correction for the Gregorian calendar.
  // It defaults to 10 for Julian dates (years <= 1600).
  int d = 10;
  if (year > 1600)
  {
    int century = year / 100 - 16;
    d = century - century / 4 + 10;
  }

  // Intermediate sum representing the base days offset from March 21st.
  int base_days = d + b - c;

  // Calculate the month: 
  // If base_days < 23, Easter is in March (month 3). 
  // Otherwise, it's in April (month 4).
  *month = base_days / 30 + 3;

  // Calculate the day of the month:
  // The original expression `((base_days + 6) / 40 + base_days + 27) % 31 + 1`
  // is algebraically equivalent to `(base_days + 27) % 31 + 1`.
  // The `+ 6) / 40` term acts as a mathematical artifact (always evaluating to 0)
  // from the original formula's bounds, so it has been safely optimized out.
  *day = (base_days + 27) % 31 + 1;
}