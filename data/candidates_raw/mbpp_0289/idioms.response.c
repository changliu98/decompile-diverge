int getweekday(int year)
{
  int hund1 = year / 100;
  int hund4 = year / 400;
  int leap = year / 4;
  int ordd = year - leap;
  if (hund1) {
    ordd += hund1;
    leap -= hund1;
  }
  if (hund4) {
    ordd -= hund4;
    leap += hund4;
  }
  return (ordd + 2 * leap) % 7;
}