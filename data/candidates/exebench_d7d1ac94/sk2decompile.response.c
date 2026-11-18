int imul_dbl(unsigned long *a) {
  unsigned long t;
  t = a[0] * a[1];
  a[0] = t;
  t >>= 32;
  t += a[0];
  a[0] = t;
  t >>= 32;
  a[1] *= a[0];
  a[1] += t;
  return (t != 0);
}