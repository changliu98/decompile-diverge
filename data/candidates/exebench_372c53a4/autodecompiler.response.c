int CTA_DateTime_ModifiedJulianToJulian(double mjd, double *jd)
{
 jd[0] = mjd + 2400000.5;
 return(0);
}