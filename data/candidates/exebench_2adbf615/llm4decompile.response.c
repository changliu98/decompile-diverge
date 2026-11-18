void daxpy(int n, double da, double *dx, double *dy)
{
 if (da == 0.0)
  return;
 if (da == 1.0) {
  while (n--)
   dy[n] += dx[n];
 } else {
  while (n--)
   dy[n] += da * dx[n];
 }
}