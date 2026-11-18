void __cdecl dxpy1(int n, const double *dx_0, double *dy)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < n; ++i )
    dy[i] = dx_0[i] + dy[i];
}