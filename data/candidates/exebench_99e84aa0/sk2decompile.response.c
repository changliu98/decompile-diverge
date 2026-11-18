char *xtoa(unsigned long x, char *s, int base, int sign) {
  char *s0 = s;
  char buf[32 + 1], *p = buf;
  do {
    *p++ = "0123456789ABCDEF"[(x % base) & 0x0f];
    x /= base;
  } while (x);
  if (sign) *p++ = '-';
  do *s++ = *--p;
  while (p != buf);
  *s = 0;
  return s0;
}