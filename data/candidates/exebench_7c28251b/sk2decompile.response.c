void sun_gpstime2mjulianday(int week, double tow, long *mjd) {
  long w;
  w = (long)(tow / 604800.0);
  *mjd = w + 44244 + 7 * week;
}