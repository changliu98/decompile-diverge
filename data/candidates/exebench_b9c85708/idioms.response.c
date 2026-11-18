void easterj(int year, int *month, int *day)
{
  int a = year % 19;
  int b = year % 4;
  int c = year % 7;
  int d = (19 * a + 15) % 30;
  int e = (2 * b + 4 * c + 6 * d + 34) % 7;
  *month = (d + e + 114) / 31;
  *day = (d + e + 114) % 31 + 1;
  return;
}