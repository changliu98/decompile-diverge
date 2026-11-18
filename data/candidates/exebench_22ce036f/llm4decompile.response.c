void foo(long n, long *p, long *q)
{
  long i;

  if (n > 0) {
    foo(n / 2, p, q);

    for (i = 1; i <= n; i++)
      *p += *q;
  }
}