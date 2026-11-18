void eastero(int year, int *month, int *day) {
  int a, b, c, d;
  a = year % 19;
  b = (19 * a + 15) % 30;
  c = (b + year / 4 + year) % 7;
  d = 10;
  if (year > 1600) d = year / 100 - 16 - (year / 100 - 16) / 4 + 10;
  *month = (b - c + d + 26) / 30 + 3;
  *day = (b - c + d + 6) / 40 + b - c + d + 27 % 31 + 1;
}