void pwm(double *series,int n,double *pwms,double A,double B,int isBeta)

{
  double dVar1;
  double F;
  double acum [3];
  int i;
  int isBeta_local;
  double B_local;
  double A_local;
  double *pwms_local;
  int n_local;
  double *series_local;
  
  acum[2] = 0.0;
  acum[1] = 0.0;
  acum[0] = 0.0;
  if ((((A != 0.0) || (NAN(A))) || (B != 0.0)) || (NAN(B))) {
    for (i = 1; i <= n; i = i + 1) {
      acum[0] = series[i + -1] + acum[0];
      dVar1 = ((double)i + A) / ((double)n + B);
      if (isBeta == 0) {
        acum[1] = series[i + -1] * (DAT_00102008 - dVar1) + acum[1];
        acum[2] = series[i + -1] * (DAT_00102008 - dVar1) * (DAT_00102008 - dVar1) + acum[2];
      }
      if (isBeta == 1) {
        acum[1] = series[i + -1] * dVar1 + acum[1];
        acum[2] = series[i + -1] * dVar1 * dVar1 + acum[2];
      }
    }
  }
  else {
    for (i = 1; i <= n; i = i + 1) {
      acum[0] = series[i + -1] + acum[0];
      if (isBeta == 0) {
        acum[1] = series[i + -1] * (double)(n - i) + acum[1];
        acum[2] = series[i + -1] * (double)(n - i) * (double)((n - i) + -1) + acum[2];
      }
      if (isBeta == 1) {
        acum[1] = series[i + -1] * (double)(i + -1) + acum[1];
        acum[2] = series[i + -1] * (double)(i + -1) * (double)(i + -2) + acum[2];
      }
    }
  }
  *pwms = acum[0] / (double)n;
  pwms[1] = (acum[1] / (double)n) / (double)(n + -1);
  pwms[2] = (acum[2] / (double)n) / (double)((n + -1) * (n + -2));
  return;
}