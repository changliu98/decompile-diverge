void SdnToJulian(long sdn, int *pYear, int *pMonth, int *pDay)
{
  int year; int month; int day;
  long yearl;
  if (sdn < 1 || sdn > 1000000000000000000 - 1 ||
      (yearl = (sdn * 4 + 128331) / 1461) > 2147483647 ||
      yearl < -2147483648)
  {
    *pYear = *pMonth = *pDay = 0;
    return;
  }
  year = (int)yearl;
  day = ((sdn * 4 + 128331) % 1461 + 1) / 4;
  month = (day * 5 - 3) / 153;
  if (month < 10)
  {
    month += 3;
  }
  else
  {
    year++;
    month -= 9;
  }
  year -= 4800;
  if (year < 1)
  {
    year--;
  }
  *pYear = year;
  *pMonth = month;
  *pDay = ((day * 5 - 3) % 153 + 1) / 5;
}