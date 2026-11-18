void sun_mjulianday_to_date(int mjulianday, int *year, int *month,
                            int *day) {
  int a, b, c, d;
  a = (mjulianday + 2432045) * 4 + 3;
  a /= 146097;
  b = a * 146097 / 4;
  c = (mjulianday + 2432045 - b) * 4 + 3;
  c /= 1461;
  d = (mjulianday + 2432045 - b - c * 1461) * 5 + 2;
  d /= 153;
  *day = mjulianday + 2432045 - b - c * 1461 - d * 153 + 1;
  *month = d + 3 - 12 * (d / 10);
  *year = d / 10 + c + 100 * a - 4800;
}