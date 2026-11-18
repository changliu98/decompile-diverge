int LI_ltostr(char *str, long l) {
  char *s, *t;
  int sign, len;
  char c;
  s = str;
  l = l;
  sign = 1;
  if (l < 0) {
    sign = 2;
    *s++ = '-';
    l = -l;
  }
  t = s;
  while (l >= 10) {
    *t++ = (l % 10) + '0';
    l /= 10;
  }
  *t++ = l + '0';
  *t = '\0';
  len = t - s + sign;
  while (s < t) {
    c = *t;
    *t = *s;
    *s = c;
    s++;
    t--;
  }
  return len;
}