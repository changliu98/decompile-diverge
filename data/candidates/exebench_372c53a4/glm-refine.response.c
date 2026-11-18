int __cdecl CTA_DateTime_ModifiedJulianToJulian(double modifiedJulianDate, double *julianDate)
{
  *julianDate = modifiedJulianDate + 2400000.5;
  return 0; // Success
}