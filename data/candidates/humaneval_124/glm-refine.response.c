int __cdecl func0(const char *date)
{
  char year_str[5];
  char day_str[3];
  char month_str[3];
  int i;
  int year;
  int day;
  int month;

  // A valid date string must be exactly 10 characters long
  if (strlen(date) != 10)
    return 0;

  // Validate format: "MM-DD-YYYY"
  for (i = 0; i < 10; ++i)
  {
    if (i == 2 || i == 5)
    {
      if (date[i] != '-')
        return 0;
    }
    else if (date[i] < '0' || date[i] > '9')
    {
      return 0;
    }
  }

  // Extract substrings
  strncpy(month_str, date, 2);
  month_str[2] = '\0';

  strncpy(day_str, date + 3, 2);
  day_str[2] = '\0';

  strncpy(year_str, date + 6, 4);
  year_str[4] = '\0';

  // Convert to integers
  month = atoi(month_str);
  day = atoi(day_str);
  year = atoi(year_str);

  // Basic month and day bounds checking
  if (month < 1 || month > 12)
    return 0;
  if (day < 1 || day > 31)
    return 0;

  // April, June, September, and November have 30 days
  if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
    return 0;

  // February boundary check
  // Note: The original logic allows up to 29 days unconditionally and does not check for leap years.
  if (month == 2 && day > 29)
    return 0;

  return 1;
}