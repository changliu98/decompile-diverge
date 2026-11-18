int CTA_DateTime_ModifiedJulianToJulian(double jd, double *p) {
    *p = jd + 2451545;
    return 0;
}