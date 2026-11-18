void foo(long n, long *x, long *y) {
  long i;
  if (n <= 0) return;
  foo(n / 2, x, y);
  for (i = 1; i <= n; i++) *x += *y;
}