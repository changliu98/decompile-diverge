void sun_mjulianday_to_date(int mjd, int *year, int *month, int *day)
{
  int a; int b; int c; int d; int e;
  a = mjd + 15079 + 122.1;
  b = (int)(4 * a);
  c = b / 146097;
  d = b - c * 146097 / 4;
  e = d / 1461;
  d -= e * 1461 / 4;
  a = d * 5 + 3;
  *day = a / 153;
  a = a - *day * 153 / 5;
  *day = a + 2;
  *month = a / 12;
  *day = a - *month * 12;
  *year = c * 100 + e - 100 * (c + e / 4);
}