int itostr(char *str, int maxlen, int val) {
  char *p, *q, c;
  int len = 0;
  if (maxlen <= 0) return 0;
  if (val < 0) {
    *str = '-';
    str++;
    maxlen--;
    len++;
    val = -val;
  }
  if (maxlen <= 0) return len;
  p = str;
  do {
    *str = (val % 10) + '0';
    str++;
    len++;
    maxlen--;
    if (maxlen <= 0) return len;
    val /= 10;
  } while (val > 0);
  *str = '\0';
  q = str - 1;
  while (p < q) {
    c = *p;
    *p = *q;
    *q = c;
    p++;
    q--;
  }
  return len;
}