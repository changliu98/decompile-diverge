void foo(long long n, long long *a, long long *b) {
  long long i;
  if (n <= 0) return;
  foo(n/2, a, b);
  for (i = 1; i <= n; i++) {
    *a += *b;
  }
}