char *int2str(int n, char *s, int base) {
  char buf[32 + 1];
  char *p, *q, *r;
  int m;
  memset(buf, 0, sizeof(buf));
  p = buf;
  q = s;
  if (base < 2 || base > 36) {
    *q = 0;
    return q;
  }
  m = n;
  if (n < 0 && base == 10) m = -n;
  do {
    *p++ = digits[m % base];
    m /= base;
  } while (m);
  if (n < 0 && base == 10) *p++ = '-';
  r = p - 1;
  while (r >= buf && (*q++ = *r--))
    ;
  *q = 0;
  return s;
}