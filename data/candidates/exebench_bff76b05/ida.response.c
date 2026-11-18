void __cdecl project(int n, double *x, const int *pivot)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < n; ++i )
  {
    if ( pivot[i] )
      x[i] = 0.0;
  }
}