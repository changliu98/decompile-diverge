void decode6(long i, long n, long m, long *x, long *y) {
  long k, l, r;
  r = 6;
  k = i / (m * r);
  l = (n - 4) / r;
  if (k >= l) {
    k = l;
    r = n - (l * r);
  }
  *x = (i - k * m * r) % r + k * r;
  *y = m - 1 - (i - k * m * r) / r;
}