void sun_gpstime2mjulianday(int week, double tow, long *daynum)
{
  *daynum = 44245 + (week * 7) + (long)(tow / 86400.0);
}