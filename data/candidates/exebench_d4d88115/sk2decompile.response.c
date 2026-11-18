void gsdate(int day, int month, int year, int *julian) {
  int m, y, j;
  y = year + 100;
  if (month > 2)
    m = month - 3;
  else {
    m = month + 9;
    y--;
  }
  j = day + (153 * m + 2) / 5 + 1461 * y / 4 - 36466;
  if (j > 59) j++;
  *julian = j;
}