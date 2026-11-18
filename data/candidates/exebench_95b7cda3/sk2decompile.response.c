void itoa(char *buf, int base, long num) {
  char *p = buf;
  char *q = buf;
  unsigned long n = num;
  int b = 10;
  int d;
  char t;
  if (base == 100 && num < 0) {
    *p++ = '-';
    n = -num;
  } else if (base == 'x') {
    b = 16;
  }
  do {
    d = n % b;
    *p++ = (d < 10) ? '0' + d : 'a' + d - 10;
    n /= b;
  } while (n);
  *p = '\0';
  p--;
  for (q = buf; q < p; q++, p--) {
    t = *q;
    *q = *p;
    *p = t;
  }
}