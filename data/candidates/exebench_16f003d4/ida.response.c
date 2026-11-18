void __cdecl calc_speed(double *x0, double *x1, double *x2, double dt)
{
  __int64 v4; // rcx
  double v5; // xmm0_8
  int j; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]

  for ( j = 0; j <= 18; j += 6 )
  {
    for ( i = 0; i < 3; ++i )
    {
      v4 = i + j;
      v5 = (x2[v4] + x0[v4]) / 2.0 - x1[v4];
      x1[(int)v4 + 3] = (v5 + v5 + (x2[v4] - x0[v4]) / 2.0) / dt;
    }
  }
}