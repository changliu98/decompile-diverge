void SdnToGregorian(long sdn, int *pYear, int *pMonth, int *pDay)
{
 int dayOfYear;
 int day;
 int month;
 int year;
 int dayOfMonth;
 int dayNumber;
 int z;

 dayNumber = (int)sdn;

 if (dayNumber < 1) {
  *pYear = 0;
  *pMonth = 0;
  *pDay = 0;
  return;
 }

 if (dayNumber > 214531) {
  *pYear = 0;
  *pMonth = 0;
  *pDay = 0;
  return;
 }

 z = dayNumber + 32044;
 dayOfYear = 4 * z + 3;
 year = (dayOfYear / 1461) * 100;
 dayOfYear = dayOfYear % 1461;

 dayOfYear = (dayOfYear / 4) * 4 + 3;
 year += dayOfYear / 1461;
 dayOfYear = dayOfYear % 1461;

 dayOfYear = (dayOfYear / 5) * 5 + 3;
 dayOfMonth = dayOfYear / 153;
 dayOfYear = dayOfYear % 153;

 if (dayOfMonth < 10) {
  month = dayOfMonth + 3;
 } else {
  month = dayOfMonth - 9;
  year++;
 }

 dayOfMonth = dayOfMonth + 1;
 day = dayOfYear / 5;
 dayOfYear = dayOfYear % 5;

 day++;
 dayOfYear = dayOfYear * 2;

 year = year - 4716;
 if (year <= 0) {
  year--;
 }

 *pYear = year;
 *pMonth = month;
 *pDay = day;
}