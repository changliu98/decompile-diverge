void easterg(int year, int *month, int *day) {
  int a, b, c, d;
  a = year % 19;
  b = year / 100;
  c = (19 * a + b - b / 4 - (b - (b + 8) / 25 + 1) / 3 + 15) % 30;
  d = (32 + 2 * (b % 4) + 2 * (b / 4) - c - a % 4) % 7;
  *month = (c + d + 114) / 31;
  *day = (c + d + 114) % 31 + 1;
}