void sun_mjulianday2date(
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
 int dayOfCentury;
 int dayOfQuadCentury;

 sdn += 2400001L;
 temp = sdn + 1402L;
 dayOfQuadCentury = ((sdn * 4L) + 272965L) / 146097L;
 dayOfCentury = ((temp * 4L) + 10803L) / 1461L;
 dayOfQuadCentury -= 2L;
 temp = dayOfQuadCentury + dayOfCentury;
 dayOfQuadCentury = (temp * 4L) + 3L;
 dayOfCentury = (dayOfQuadCentury / 1461L) - 100L;
 dayOfQuadCentury = (dayOfQuadCentury % 1461L) / 4L;
 dayOfQuadCentury += dayOfCentury;
 dayOfQuadCentury += 2L;
 dayOfCentury = (dayOfQuadCentury / 153L) + 1L;
 dayOfQuadCentury = (dayOfQuadCentury % 153L) + 1L;
 day = (int)dayOfQuadCentury;
 month = (int)((dayOfQuadCentury / 12L) + 2L);
 month %= 12L;
 ++month;
 year = (int)dayOfCentury - 4800L;
 year += ((14 - month) / 12L);
 *pYear = year;
 *pMonth = month;
 *pDay = day;
}