void sun_gpstime2mjulianday(
    int week,
    double tow,
    long *daynum
) {
 *daynum = (long)(week*7) + (long)(tow/(7*(60*60*24)))
     + 44244;
}