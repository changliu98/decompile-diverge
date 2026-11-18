void dxpy1(int n, double *dx, double *dy)
{
  int i;
  for (i = 0; i < n; i++)
    dy[i] += dx[i];
}