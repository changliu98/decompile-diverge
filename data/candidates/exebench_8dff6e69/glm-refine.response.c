void __cdecl dxpy1(int n, const double *dx, double *dy)
{
  for (int i = 0; i < n; ++i)
    dy[i] += dx[i];
}