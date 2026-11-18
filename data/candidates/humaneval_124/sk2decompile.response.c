int _is_date(char *str) {
  char *s = str;
  int i;
  char month[3];
  char day[3];
  char year[5];
  int m, d, y;
  if (strlen(s) != 10) return 0;
  for (i = 0; i < 10; i++) {
    if (i == 2 || i == 5) {
      if (s[i] != '-') return 0;
    } else {
      if (s[i] < '0' || s[i] > '9') return 0;
    }
  }
  month[0] = s[0];
  month[1] = s[1];
  month[2] = '\0';
  day[0] = s[3];
  day[1] = s[4];
  day[2] = '\0';
  year[0] = s[6];
  year[1] = s[7];
  year[2] = s[8];
  year[3] = s[9];
  year[4] = '\0';
  m = atoi(month);
  d = atoi(day);
  y = atoi(year);
  if (m < 1 || m > 12) return 0;
  if (d < 1 || d > 31) return 0;
  if ((m == 4 || m == 6 || m == 9 || m == 11) && d == 31) return 0;
  if (m == 2 && d > 29) return 0;
  return 1;
}