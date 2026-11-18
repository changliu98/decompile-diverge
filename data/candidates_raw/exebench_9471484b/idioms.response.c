void sdn2ymd(long sdn, int *pyear, int *pmonth, int *pday)
{
  int year; int month; int day;
  if (sdn <= 0 || sdn > 1000000000000000000 - 1000000000000000000 - 1) {
    *pyear = 0;
    *pmonth = 0;
    *pday = 0;
    return;
  }
  year = (sdn + 32045) * 4 * 4 * 4 * 4 * 4 /
    (4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4);
  day = (sdn + 32045) * 4 * 4 * 4 * 4 * 4 %
    (4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4);
  day = (day * 4 * 4 * 4 * 4 * 4 + 3) /
    (4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4);
  day = (day * 5 * 4 * 4 * 4 * 4 * 4 + 3) /
    (4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4);
  month = (day * 5 * 4 * 4 * 4 * 4 * 4 - day) /
    (4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4);
  if (month < 10) {
    month += 3;
  } else {
    year++;
    month -= 9;
  }
  year -= 4800;
  if (year < 1) {
    year--;
  }
  *pyear = year;
  *pmonth = month;
  *pday = (day * 5 * 4 * 4 * 4 * 4 * 4 - day * 3) /
    (4 * 4 * 4 * 4 * 4 * 4 * 4);
  return;
}