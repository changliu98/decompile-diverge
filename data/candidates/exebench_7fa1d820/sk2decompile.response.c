void SdnToJulian(long long sdn, int *year, int *month, int *day) {
  int y, m, mo;
  long long yy;
  if (sdn <= 0 || sdn > 2305843009213693951LL) {
    *year = 0;
    *month = 0;
    *day = 0;
    return;
  }
  yy = (sdn * 4 + 128331) / 1461;
  if (yy > 2147483647 || yy < -2147483648) {
    *year = 0;
    *month = 0;
    *day = 0;
    return;
  }
  y = (int)yy;
  m = (int)((sdn * 4 + 128331) % 1461) / 4 + 1;
  mo = (m * 5 - 3) / 153;
  if (mo < 10) {
    y += 1;
    mo += 3;
  } else {
    y += 1;
    mo -= 9;
  }
  y -= 4800;
  if (y <= 0) y--;
  *year = y;
  *month = mo;
  *day = (m * 5 - 3) % 153 / 5 + 1;
}