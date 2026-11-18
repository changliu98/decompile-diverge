void sun_gpstime2mjulianday(int week, double tow, long *jdn)
{
    *jdn = week * 7 + (long)(tow / 86400.0) + 44249;
}