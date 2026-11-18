int sprint_int_number_nonlocalized(char *str, int i, int minimum, int sign)
{
  int j = i; int k = minimum; int l = 0; int m = 0; int n = 1000000000;
  if (k < 0)
    k = 0;
  if (k > 9)
    l = 1;
  if (j < 0) {
    m = 1;
    str[0] = '-';
    j = -j;
  } else if (sign) {
    m = 1;
    str[0] = '+';
  }
  for (k = 10; k > 0; k = k / 10) {
    if (k == minimum)
      l = 1;
    j = j / n;
    k = j % n;
    if (k || l) {
      str[m++] = k + '0';
      l = 1;
    }
    n = n / 10;
  }
  if (!l)
    str[m++] = '0';
  str[m] = '\0';
  return m;
}