void pwm(double series[], int n, double pwms[], double A, double B, int isBeta) {
  int i;
  double acum[3] = {0,0,0};
  double pwm;

  if (A==0 && B==0) {
    for (i=1; i<=n; i++) {
      acum[0] += series[i-1];
      if (isBeta==0) {
        acum[1] += series[i-1]*(n-i);
        acum[2] += series[i-1]*(n-i)*(n-i-1);
      }
      if (isBeta==1) {
        acum[1] += series[i-1]*(i-1);
        acum[2] += series[i-1]*(i-1)*(i-2);
      }
    }
  } else {
    for (i=1; i<=n; i++) {
      acum[0] += series[i-1];
      pwm = ((double)i+A)/((double)n+B);
      if (isBeta==0) {
        acum[1] += series[i-1]*(1-pwm);
        acum[2] += series[i-1]*(1-pwm)*(1-pwm);
      }
      if (isBeta==1) {
        acum[1] += series[i-1]*pwm;
        acum[2] += series[i-1]*pwm*pwm;
      }
    }
  }

  pwms[0] = acum[0]/n;
  pwms[1] = acum[1]/n/(n-1);
  pwms[2] = acum[2]/n/(n-1)/(n-2);
}