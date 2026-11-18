void sun_mjulianday_to_date(mjd, year, month, day)
int mjd;
int *year;
int *month;
int *day;
{
   int jd, l, n, i, j, k;

   jd = mjd + 2499782 + 32083;
   l = jd + 68569;
   n = ( 4 * l ) / 146097;
   i = l - ( 146097 * n + 3 ) / 4;
   j = ( 4000 * ( i + 1 ) ) / 1461001;
   k = i - ( 1461 * j ) / 4 + 1;
   *day = ( 80 * k + 2 ) / 2447;
   *month = k + 2 - ( 12 * *day / 32);
   *year = 100 * ( n - 49 ) + j + *day - 32083;
}