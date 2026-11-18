void __cdecl sun_mjulianday2date(long daynum, int *year, int *month, int *day)
{
  int h; // [rsp+8h] [rbp-30h]

  h = 5 * ((int)(4 * (3 * ((4 * (daynum + 2400001) + 274277) / 146097) / 4 + daynum + 2401402 - 38) + 3) % 1461 / 4) + 2;
  *day = h % 153 / 5 + 1;
  *month = (h / 153 + 2) % 12 + 1;
  *year = (14 - *month) / 12
        + (int)(4 * (3 * ((4 * (daynum + 2400001) + 274277) / 146097) / 4 + daynum + 2401402 - 38) + 3) / 1461
        - 4716;
}