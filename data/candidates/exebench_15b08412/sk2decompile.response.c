int div_dbl(unsigned long long *a, unsigned long long b) {
  unsigned long long t;
  if (b == 0) return 1;
  if (a[1] >= b) return 1;
  t = a[0];
  a[0] = t / b;
  a[1] = t % b;
  return 0;
}