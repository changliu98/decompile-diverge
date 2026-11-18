// Checks if the given month number represents a month with 31 days.
bool __cdecl IsMonthWith31Days(int month)
{
  return month == 1  // January
      || month == 3  // March
      || month == 5  // May
      || month == 7  // July
      || month == 8  // August
      || month == 10 // October
      || month == 12; // December
}