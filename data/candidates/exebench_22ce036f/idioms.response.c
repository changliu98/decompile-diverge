void foo(long n, long *p, long *q)
{
  if ( n > 0 )
  {
    foo( n / 2, p, q);
    for ( long i = 1; i <= n; i++ )
      *p += *q;
  }
}