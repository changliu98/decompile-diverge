void easterj(int year, int *month, int *day) {
  int a, b, c;
  a = year % 19;
  b = year % 4;
  c = year % 7;
  *month = (34 + 7 * a + 2 * b - c + 19 * a + 15) / 30;
  *day = (34 + 7 * a + 2 * b - c + 19 * a + 15) % 30 + 1;
}