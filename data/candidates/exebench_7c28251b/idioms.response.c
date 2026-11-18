void sun_gpstime2mjulianday(int week, double tow, long *daynum)
{
  *daynum = (int)(tow / 604800) + (week * 7) + 44244;
}