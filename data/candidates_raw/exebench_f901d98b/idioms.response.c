void calc_pwms(double *series, int n, double *pwms, double A, double B, int isBeta){
  int i;
  double F;
  double acum = 0.0;
  double acum2 = 0.0;
  double acum3 = 0.0;
  if (A == 0 && B == 0){
    for (i = 1; i <= n; i++){
      acum += series[i-1];
      if (isBeta == 0){
        acum2 += (n-i)*series[i-1];
        acum3 += (n-i)*(n-i-1)*series[i-1];
      }
      if (isBeta == 1){
        acum2 += (i-1)*series[i-1];
        acum3 += (i-1)*(i-2)*series[i-1];
      }
    }
  }
  else {
    for (i = 1; i <= n; i++){
      acum += series[i-1];
      F = (double)i + A / (double)n + B;
      if (isBeta == 0){
        acum2 += (1-F)*series[i-1];
        acum3 += (1-F)*(1-F)*series[i-1];
      }
      if (isBeta == 1){
        acum2 += F*series[i-1];
        acum3 += F*F*series[i-1];
      }
    }
  }
  pwms[0] = acum / (double)n;
  pwms[1] = acum2 / (double)n / (double)(n-1);
  pwms[2] = acum3 / (double)n / (double)(n-1)*(double)(n-2);
}