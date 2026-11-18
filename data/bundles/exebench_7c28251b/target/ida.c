void __cdecl sun_gpstime2mjulianday(int week, double tow, long *daynum)
{
  *daynum = (unsigned int)(int)(tow / 604800.0) + (__int64)(7 * week) + 44244;
}