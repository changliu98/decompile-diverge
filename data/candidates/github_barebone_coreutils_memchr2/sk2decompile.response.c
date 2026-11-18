void *memchr2(const void *s, int c1, int c2, size_t n) {
  unsigned char *p;
  unsigned long *pl;
  unsigned long lc1, lc2;
  unsigned char uc1 = (unsigned char)c1;
  unsigned char uc2 = (unsigned char)c2;
  if (uc1 == uc2) return memchr(s, uc1, n);
  for (p = (unsigned char *)s; n && ((unsigned long)p & (sizeof(long) - 1));
       n--, p++)
    if (*p == uc1 || *p == uc2) return (void *)p;
  pl = (unsigned long *)p;
  lc1 = (uc1 << 8) | uc1;
  lc1 |= lc1 << 16;
  lc1 |= lc1 << 32;
  lc2 = (uc2 << 8) | uc2;
  lc2 |= lc2 << 16;
  lc2 |= lc2 << 32;
  while (n >= sizeof(long) * 2 &&
         !((((*pl ^ lc1) - 0x0101010101010101ULL) & ~(*pl ^ lc1)) &
           0x8080808080808080ULL) &&
         !((((*pl ^ lc2) - 0x0101010101010101ULL) & ~(*pl ^ lc2)) &
           0x8080808080808080ULL)) {
    pl++;
    n -= sizeof(long);
  }
  p = (unsigned char *)pl;
  while (n) {
    if (*p == uc1 || *p == uc2) return (void *)p;
    n--;
    p++;
  }
  return NULL;
}