void gps2jdn(int week, double tow, long *jdn)
{
    *jdn = week * 7 + (long)(tow / 86400.0) + 44249;
}