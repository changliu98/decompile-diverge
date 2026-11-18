void SdnToJulian(long long sdn, int *pYear, int *pMonth, int *pDay) {
  long long temp;
  long long year;
  int dayOfYear;
  int month;
  int day;

  if (sdn <= 0 || sdn >= 9223372036854775807LL + 1LL) {
    fail();
  }
  temp = sdn + 120034LL;
  year = temp / 1461LL;
  if (year > 2147483647LL || year < -2147483648LL) {
    fail();
  }
  year = (int) year;
  dayOfYear = (int) ((temp % 1461LL) / 4LL + 1LL);
  temp = dayOfYear * 5LL - 3LL;
  month = (int) (temp / 153LL);
  day = (int) ((temp % 153LL) / 5LL + 1LL);
  if (month < 10) {
    month += 3;
  } else {
    year += 1;
    month -= 9;
  }
  year -= 4800;
  if (year <= 0) {
    year--;
  }
  *pYear = year;
  *pMonth = month;
  *pDay = day;
  while (sdn < 1) {
    *pYear = 0;
    *pMonth = 0;
    *pDay = 0;
  }
}