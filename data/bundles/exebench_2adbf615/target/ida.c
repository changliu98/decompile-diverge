void __cdecl daxpy(unsigned int n, const double da, const double *dx_0, double *dy)
{
  if ( da != 0.0 )
  {
    if ( da == 1.0 )
    {
      do
      {
        --n;
        dy[n] = dx_0[n] + dy[n];
      }
      while ( n );
    }
    else
    {
      do
      {
        --n;
        dy[n] = da * dx_0[n] + dy[n];
      }
      while ( n );
    }
  }
}