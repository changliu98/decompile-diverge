int itostr(char *str, int len, int i)
{
  char *s = str;
  int l = len;
  int n = i;
  int ret = 0;
  if (len <= 0)
    return 0;
  if (n < 0) {
    *str = '-';
    str++;
    len--;
    ret++;
    n = -n;
  }
  if (len <= 0)
    return ret;
  char *start = str;
  do {
    *str = n % 10 + '0';
    str++;
    ret++;
    if (--len <= 0)
      return ret;
    n /= 10;
  } while (n > 0);
  *str = '\0';
  str = str - 1;
  for ( ; start < str; start++) {
    char tmp = *start;
    *start = *str;
    *str = tmp;
    str++;
  }
  return ret;
}