void daxpy(int n, double a, double *dx, double *dy)
{
  if (a == 0.)
    return;
  if (a == 1.)
    for ( ; n--; )
      dy[n] += dx[n];
  else
    for ( ; n--; )
      dy[n] += a * dx[n];
}