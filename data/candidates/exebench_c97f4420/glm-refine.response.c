void __cdecl get_month_and_day_by_row(const int row, const int year, int *const month, int *const day)
{
  // The original code copies a static array of 12 integers from the .rdata section.
  // unk_2030 represents the standard number of days in each month.
  int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int monthdays = 0;
  bool is_leap;

  *day = 0;
  *month = 0;

  // Reconstructed leap year logic from the decompiled bitwise/boolean operations
  if (year % 4 != 0) {
    is_leap = false;
  } else if (year % 100 != 0) {
    is_leap = true;
  } else {
    is_leap = (year % 400 == 0);
  }

  // Validate that the row falls within the valid number of days for the year
  if (row > 0 && row <= is_leap + 365)
  {
    if (is_leap)
      ++days_in_month[1]; // February has 29 days in a leap year

    // Iterate through months until we find the month containing the target row
    while (row > monthdays)
    {
      int current_month = (*month)++;
      monthdays += days_in_month[current_month];
    }

    // Calculate the exact day within the found month
    *day = days_in_month[*month - 1] + row - monthdays;
  }
}