void __cdecl foo(long n, long *p, long *q)
{
  if (n > 0)
  {
    foo(n / 2, p, q);
    
    // Unrolled loop: adds *q to *p exactly 'n' times
    *p += n * *q;
  }
}