void SdnToGregorian(long julianDay, int* pYear, int* pMonth, int* pDay) {
 long sdn;
 int century;
 int year;
 int month;
 int day;
 int dayOfYear;

 if (julianDay < 1 || julianDay > 32767L + 32767L + 365L)
  goto fail;

 sdn = (julianDay + 32767L + 365L) * 4L - 1L;
 century = sdn / 146097L;
 sdn = ((sdn % 146097L) / 4L) * 4L + 3L;
 year = century * 100L + sdn / 1461L;
 dayOfYear = (sdn % 1461L) / 4L + 1L;
 sdn = dayOfYear * 5L - 3L;
 month = sdn / 153L;
 day = (sdn % 153L) / 5L + 1L;
 if (month < 10)
  month += 3;
 else
 {
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