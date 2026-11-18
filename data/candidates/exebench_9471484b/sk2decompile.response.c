void SdnToGregorian(long long sdn, int *year, int *month, int *day) {
  int y, a, b;
  int c, d;
  if (sdn <= 0 || sdn > 2305843009213693952LL) {
    *year = 0;
    *month = 0;
    *day = 0;
    return;
  }
  y = (int)((4 * (sdn + 32045) - 1) / 146097);
  a = (4 * (sdn + 32045) - 1) % 146097;
  b = (a / 4 + 3) % 1461;
  c = b / 4 + 1;
  d = (5 * c - 3) / 153;
  if (d < 10)
    d += 3;
  else {
    d -= 9;
    y++;
  }
  y *= 100;
  y += (b / 4 + 1);
  y -= 4800;
  if (y <= 0) y--;
  *year = y;
  *month = d;
  *day = (5 * c - 3) % 153 / 5 + 1;
}