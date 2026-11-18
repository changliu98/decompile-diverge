static void shr(unsigned long *a, int n) {
  if ((unsigned long)n >= 64) {
    n -= 64;
    a[0] = a[1];
    a[1] = 0;
  }
  a[0] >>= n;
  a[0] |= a[1] << (64 - n);
  a[1] >>= n;
}