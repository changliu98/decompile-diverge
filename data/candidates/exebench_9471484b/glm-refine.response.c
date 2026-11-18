void __cdecl SdnToGregorian(long sdn, int *pYear, int *pMonth, int *pDay)
{
  // Check if the SDN (Serial Day Number) is within the valid range
  if (sdn > 0 && sdn <= 0x1FFFFFFFFFFF82D2LL)
  {
    long l1 = sdn + 32045;
    long l2 = (4 * l1 - 1) % 146097;
    long l3 = l2 / 4;
    long l4 = 4 * l3 + 3;
    
    // Calculate year and day of year
    int year = l4 / 1461 + 100 * ((4 * l1 - 1) / 146097);
    int dayOfYear = l4 % 1461 / 4 + 1;
    
    // Calculate month
    int month = (5 * dayOfYear - 3) / 153;
    
    // Adjust year and month based on the calculated month
    if (month >= 10)
    {
      ++year;
      month -= 9;
    }
    else
    {
      month += 3;
    }
    
    // Adjust for astronomical year numbering (1 BC = 0, 2 BC = -1, etc.)
    if (year <= 4800)
      --year;
    
    year -= 4800;
    
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