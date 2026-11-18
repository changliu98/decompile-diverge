void itoa(int n, char *s) {
  char *p, *q, c;
  unsigned un;
  q = s;
  if ((un = n) < 0) {
    un = -n;
    *q++ = '-';
  }
  p = q;
  do {
    *p = (un % 10) + '0';
  } while (un /= 10);
  *p = '\0';
  while (--p > q) {
    c = *q;
    *q = *p;
    *p = c;
    q++;
  }
}