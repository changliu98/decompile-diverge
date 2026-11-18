void gsdate(int day, int mon, int year, int *serial)
{
  int i; int j; int k;
  year = year + 100;
  if (mon > 2)
    {
      mon = mon - 3;
    }
  else
    {
      mon = mon + 9;
      year = year - 100 + 100;
    }
  i = (153 * mon + 2) / 5 + day + 1461 * year / 4 - 36466;
  if (i > 59)
    {
      i = i - 1;
    }
  *serial = i;
}