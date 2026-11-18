void j2gcal(double jd, int *year, int *month, int *day) {
  int l, n, i, j;
  l = (int)(jd + 0.5);
  n = 4 * (l + 68569) / 146097;
  l = l + 68569 - (146097 * n + 3) / 4;
  i = 4000 * (l + 1) / 1461001;
  l = l - 1461 * i / 4 + 31;
  j = 80 * l / 2447;
  *day = l - 2447 * j / 80;
  *month = j + 2 - 12 * (j / 11);
  *year = i + 100 * (n - 49);
}