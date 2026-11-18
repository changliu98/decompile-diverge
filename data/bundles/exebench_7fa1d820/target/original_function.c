void SdnToJulian(
     long int sdn,
     int *pYear,
     int *pMonth,
     int *pDay)
{
 int year;
 int month;
 int day;
 long int temp;
 int dayOfYear;

 if (sdn <= 0) {
  goto fail;
 }

 if (sdn > (LONG_MAX - 32083 * 4 + 1) / 4 || sdn < LONG_MIN / 4) {
  goto fail;
 }
 temp = sdn * 4 + (32083 * 4 - 1);


 {
  long yearl = temp / 1461;
  if (yearl > INT_MAX || yearl < INT_MIN) {
   goto fail;
  }
  year = (int) yearl;
 }
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