void __cdecl foo(long n, long *p, long *q)
{
  long i; // [rsp+0h] [rbp-20h]

  if ( n > 0 )
  {
    foo(n / 2, p, q);
    for ( i = 1LL; i <= n; ++i )
      *p += *q;
  }
}