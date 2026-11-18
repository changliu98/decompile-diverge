void easterg(int year, int *month, int *day)
{
  int a; int b; int c; int d; int e;
  a = (year / 100) + 19 * (year % 19);
  a = a - (a / 4);
  a = a - (a / 100 * 3);
  a = a + 15;
  a = a % 30;
  b = (year % 100) / 4;
  c = (year / 100) % 4;
  d = 2 * b + 2 * c;
  d = d - a - (year % 100);
  d = d % 7;
  e = (22 * d + 11 * a);
  e = e + (year % 19);
  e = e / 451;
  *month = (d + a - 7 * e + 114) / 31;
  *day = (d + a - 7 * e + 114) % 31 + 1;
}