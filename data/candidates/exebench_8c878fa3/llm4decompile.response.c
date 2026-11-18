void sun_mjulianday_to_date(int mjd, int *year, int *month, int *day)
{
 int f, e, d, c, b, a;

 f = mjd + 2400000 + 68569;
 b = 4 * f + 3;
 b = b / 146097;
 a = f - (146097 * b) / 4;

 d = 4 * a + 3;
 d = d / 1461;
 c = a - (1461 * d) / 4;

 f = 5 * c + 2;
 b = f / 153;
 *day = c - (153 * b + 2) / 5 + 1;
 *month = b + 3 - 12 * (b / 10);
 *year = b / 10 - 4800 + d - 4000 + 100 * b;
}