void SdnToGregorian(
        long int sdn,
        int *pYear,
        int *pMonth,
        int *pDay)
{
 int century;
 int year;
 int month;
 int day;
 long int temp;
 int dayOfYear;

 if (sdn <= 0 ||
   sdn > (LONG_MAX - 4 * 32045) / 4) {
  goto fail;
 }
 temp = (sdn + 32045) * 4 - 1;


 century = temp / 146097;


 temp = ((temp % 146097) / 4) * 4 + 3;
 year = (century * 100) + (temp / 1461);
 dayOfYear = (temp % 1461) / 4 + 1;


 temp = dayOfYear * 5 - 3;
 month = temp / 153;
 day = (temp % 153) / 5 + 1;


 if (month < 10) {
  month += 3;
 } else {
  year += 1;
  month -= 9;
 }


 year -= 4800;
 if (year <= 0)
  year--;

 *pYear = year;
 *pMonth = month;
 *pDay = day;
 return;

fail:
 *pYear = 0;
 *pMonth = 0;
 *pDay = 0;
}