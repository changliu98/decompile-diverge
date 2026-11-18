int __cdecl clipmaxdouble(double *x, double xmax, long n)
{
  long i; // [rsp+0h] [rbp-20h]

  for ( i = 0LL; i < n; ++i )
  {
    if ( x[i] > xmax )
      x[i] = xmax;
  }
  return 0;
}