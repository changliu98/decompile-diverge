void eastero(int year, int *month, int *day)
{
  int a; int b; int c; int d;
  a = (year % 19 * 19 + 15) % 30;
  b = (year / 4 + year) % 7;
  c = a + b + 10;
  d = c - c / 25 * 25 - c / 25 * 3 - 2;
  if (year > 1600)
  {
    d += (year / 100 - 16 - (year / 100 - 16) / 4) * 10;
  }
  *month = (d + a - c + 26) / 30 + 3;
  *day = (d + a - c + 6) / 40 + d + a - c + 27 - (*month - 3) * 30;
  *day = *day % 31 + 1;
}