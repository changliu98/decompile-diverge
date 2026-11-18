void gsdate(int day, int mon, int year, int *serial)
{
 int m, y, d;

 y = year + 100;
 if (mon < 3) {
  m = mon + 9;
  y--;
 } else {
  m = mon - 3;
 }
 d = day;
 *serial = 365 * (y - 1) + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400 + (m * 153 + 2) / 5 + d - 36211;
 if (*serial > 58480)
  *serial--;
}