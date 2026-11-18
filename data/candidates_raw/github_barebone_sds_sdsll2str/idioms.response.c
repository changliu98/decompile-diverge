int itostr(char *str, long long val)
{
  char *s = str;
  char *t = str;
  char tmp;
  unsigned long long uval;
  int len;
  if (val < 0) {
    if (val == -1)
      uval = 18446744073709551615UL;
    else
      uval = (unsigned long long)-val;
  } else
    uval = (unsigned long long)val;
  do {
    *t++ = uval % 10 + '0';
  } while (uval /= 10);
  if (val < 0)
    *t++ = '-';
  len = t - s;
  *t = '\0';
  for (t--; s < t; s++) {
    tmp = *s;
    *s = *t;
    *t = tmp;
    t--;
  }
  return len;
}