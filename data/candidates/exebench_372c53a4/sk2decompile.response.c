int CTA_DateTime_ModifiedJulianToJulian(double modified_julian_day,
                                        double *julian_day) {
  *julian_day = modified_julian_day + 2400000.5;
  return 0;
}