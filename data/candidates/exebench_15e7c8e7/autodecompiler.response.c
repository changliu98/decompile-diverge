void j2gcal(double jd, int* year, int* month, int* day) {
  int i, j, k, l, n, z, alpha;
  z = (int)(jd + 0.5);
  i = (int)((4 * z - 1) / 146097) + 15;
  j = 4 * z - 1 - 146097 * i;
  k = (int)((j - 1) / 4);
  l = z - k + 31;
  n = (int)((80 * l - 2447) / 153);
  *day = l - (int)((153 * n + 2) / 12) - 32;
  *month = n + 2 - (int)(n / 11);
  *year = i - 4716 + (int)((n + 2) / 11);
}