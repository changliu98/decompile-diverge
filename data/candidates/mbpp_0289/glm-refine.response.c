// This function calculates the day of the week for December 31st of a given year N.
// It returns 0 for Sunday, 1 for Monday, ..., 6 for Saturday.
// The logic is based on counting the total number of days modulo 7.
int __cdecl get_day_of_week(int year)
{
  int ordinary_years; // Total count of non-leap years
  int leap_years;     // Total count of leap years
  int century_years;  // Count of years divisible by 100
  int quad_centuries; // Count of years divisible by 400

  century_years = year / 100;
  quad_centuries = year / 400;
  
  // year >> 2 is equivalent to year / 4
  leap_years = year / 4;
  
  // Start by assuming all years are ordinary (non-leap)
  ordinary_years = year - (year / 4);

  // Years divisible by 100 are NOT leap years unless they are also divisible by 400.
  // So, we subtract them from leap_years and add them to ordinary_years.
  if (century_years)
  {
    ordinary_years += century_years;
    leap_years -= century_years;
  }

  // Years divisible by 400 ARE leap years.
  // So, we add them back to leap_years and subtract them from ordinary_years.
  if (quad_centuries)
  {
    ordinary_years -= quad_centuries;
    leap_years += quad_centuries;
  }

  // Total days = (leap_years * 366) + (ordinary_years * 365)
  // Modulo 7 of the total days gives the day of the week.
  // Mathematically, (366 * leap + 365 * ord) % 7 simplifies to:
  // (2 * leap + ordd) % 7
  return (2 * leap_years + ordinary_years) % 7;
}