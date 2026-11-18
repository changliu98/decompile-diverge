int itoa(int val, char *str)
{
  int i;
  int len;
  int tmp;
  char *s;
  char *t;
  char c;
  int v;
  v = val;
  s = str;
  if (v < 0) {
    *s++ = '-';
    v = -val;
  }
  t = s;
  do {
    *t++ = (v % 10) + '0';
  } while (v /= 10);
  *t = '\0';
  len = t - s;
  for (i = 0; i < len / 2; i++) {
    c = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = c;
  }
  return t - s;
}