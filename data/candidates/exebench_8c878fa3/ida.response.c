void __cdecl sun_mjulianday_to_date(unsigned int mjd, int *year, int *month, int *day)
{
  int m; // [rsp+8h] [rbp-38h]
  int d; // [rsp+10h] [rbp-30h]
  int b; // [rsp+18h] [rbp-28h]

  b = (int)(4 * (mjd + 2432045) + 3) / 146097;
  d = (int)(4 * (mjd + 2432045 - 146097 * b / 4) + 3) / 1461;
  m = (int)(5 * (mjd + 2432045 - 146097 * b / 4 - 1461 * d / 4) + 2) / 153;
  *day = mjd + 2432045 - 146097 * b / 4 - 1461 * d / 4 - (153 * m + 2) / 5 + 1;
  *month = m + 3 - 12 * (m / 10);
  *year = m / 10 + d + 100 * b - 4800;
}