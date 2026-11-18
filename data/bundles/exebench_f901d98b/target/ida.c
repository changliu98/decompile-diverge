void __cdecl pwm(double *series, int n, double *pwms, double A, double B, int isBeta)
{
  double F; // [rsp+0h] [rbp-58h]
  double acum; // [rsp+8h] [rbp-50h]
  double acum_8; // [rsp+10h] [rbp-48h]
  double acum_16; // [rsp+18h] [rbp-40h]
  int i; // [rsp+28h] [rbp-30h]
  int ia; // [rsp+28h] [rbp-30h]

  acum_16 = 0.0;
  acum_8 = 0.0;
  acum = 0.0;
  if ( A == 0.0 && B == 0.0 )
  {
    for ( i = 1; i <= n; ++i )
    {
      acum = series[i - 1] + acum;
      if ( !isBeta )
      {
        acum_8 = series[i - 1] * (double)(n - i) + acum_8;
        acum_16 = series[i - 1] * (double)(n - i) * (double)(n - i - 1) + acum_16;
      }
      if ( isBeta == 1 )
      {
        acum_8 = series[i - 1] * (double)(i - 1) + acum_8;
        acum_16 = series[i - 1] * (double)(i - 1) * (double)(i - 2) + acum_16;
      }
    }
  }
  else
  {
    for ( ia = 1; ia <= n; ++ia )
    {
      acum = series[ia - 1] + acum;
      F = ((double)ia + A) / ((double)n + B);
      if ( !isBeta )
      {
        acum_8 = series[ia - 1] * (1.0 - F) + acum_8;
        acum_16 = series[ia - 1] * (1.0 - F) * (1.0 - F) + acum_16;
      }
      if ( isBeta == 1 )
      {
        acum_8 = series[ia - 1] * F + acum_8;
        acum_16 = series[ia - 1] * F * F + acum_16;
      }
    }
  }
  *pwms = acum / (double)n;
  pwms[1] = acum_8 / (double)n / (double)(n - 1);
  pwms[2] = acum_16 / (double)n / (double)((n - 2) * (n - 1));
}