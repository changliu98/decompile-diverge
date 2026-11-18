int __cdecl CTA_DateTime_ModifiedJulianToJulian(double mjd, double *jd)
{
  *jd = mjd + 2400000.5;
  return 0;
}