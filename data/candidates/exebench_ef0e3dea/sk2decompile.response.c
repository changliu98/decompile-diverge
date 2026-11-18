void sun_mjulianday2date(long year, int *month, int *day, int *day_of_week) {
  int mjd, d, w;
  mjd = year + 2400001;
  mjd = 4 * mjd + 274277;
  mjd = mjd / 146097;
  mjd = 4 * mjd + 3;
  mjd = (mjd / 1461) * 4 + 3;
  mjd = mjd / 153;
  d = mjd / 5 + 1;
  w = mjd % 5 + 1;
  *day_of_week = w;
  *day = d;
  *month = mjd / 153 + 2;
  *month = (*month % 12) + 1;
  *year = mjd / 153 - 1;
  *year = (*year + 4) / 12;
  *year = *year - 4716;
}