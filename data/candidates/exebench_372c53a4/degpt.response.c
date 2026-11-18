int CTA_DateTime_ModifiedJulianToJulian(double mjd,double *jd)

{
  double *jd_local;
  double mjd_local;
  
  *jd = DAT_00102008 + mjd;
  return 0;
}