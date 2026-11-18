void SdnToJulian(long sdn, int *pYear, int *pMonth, int *pDay)
{
 int dayOfYear;
 int dayOfMonth;
 int day;
 int month;
 int year;

 if (sdn > 0 && sdn < 2145356800L) {
  dayOfYear = (int)((sdn - 1948440L) % 1461 / 4);
  year = (int)((sdn - 1948440L) / 1461);
  year = 4 * year + dayOfYear / 1460;
  dayOfYear = dayOfYear % 1460;


  dayOfMonth = dayOfYear / 153;
  dayOfYear = dayOfYear % 153;

  if (dayOfMonth < 10) {
   month = dayOfMonth - 2;
  } else {
   month = dayOfMonth - 10;
   year++;
  }

  day = dayOfYear / 5 + 1;
  year += 3204;
  if (year <= 0) {
   year--;
  }

  *pYear = year;
  *pMonth = month;
  *pDay = day;
 } else {
  *pYear = 0;
  *pMonth = 0;
  *pDay = 0;
 }
}