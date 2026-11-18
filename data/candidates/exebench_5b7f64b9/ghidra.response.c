int dspline(double *x,double *y,int n,int if1,double cond1,int ifn,double condn,double *y2)

{
  double dVar1;
  double dVar2;
  double sig;
  double un;
  double qn;
  double u [2000];
  double p;
  int k;
  int i__;
  int i__1;
  double *y2_local;
  double condn_local;
  int ifn_local;
  double cond1_local;
  int if1_local;
  int n_local;
  double *y_local;
  double *x_local;
  int local_c;
  
  if (n < 0x7d1) {
    if (if1 == 2) {
      *y2 = 0.0;
      u[0] = cond1;
    }
    else {
      if (if1 != 1) {
        return 2;
      }
      *y2 = DAT_00102010;
      u[0] = (DAT_00102008 / (x[1] - *x)) * ((y[1] - *y) / (x[1] - *x) - cond1);
    }
    for (i__ = 2; i__ <= n + -1; i__ = i__ + 1) {
      dVar1 = (x[(long)i__ + -1] - x[(long)(i__ + -1) + -1]) /
              (x[(long)(i__ + 1) + -1] - x[(long)(i__ + -1) + -1]);
      dVar2 = dVar1 * y2[(long)(i__ + -1) + -1] + DAT_00102030;
      y2[(long)i__ + -1] = (dVar1 - DAT_00102020) / dVar2;
      u[i__ + -1] = (-dVar1 * u[i__ + -2] +
                    (((y[(long)(i__ + 1) + -1] - y[(long)i__ + -1]) /
                      (x[(long)(i__ + 1) + -1] - x[(long)i__ + -1]) -
                     (y[(long)i__ + -1] - y[(long)(i__ + -1) + -1]) /
                     (x[(long)i__ + -1] - x[(long)(i__ + -1) + -1])) * DAT_00102028) /
                    (x[(long)(i__ + 1) + -1] - x[(long)(i__ + -1) + -1])) / dVar2;
    }
    if (ifn == 2) {
      qn = 0.0;
      un = condn;
    }
    else {
      if (ifn != 1) {
        return 3;
      }
      qn = DAT_00102018;
      un = (DAT_00102008 / (x[(long)n + -1] - x[(long)(n + -1) + -1])) *
           (condn - (y[(long)n + -1] - y[(long)(n + -1) + -1]) /
                    (x[(long)n + -1] - x[(long)(n + -1) + -1]));
    }
    y2[(long)n + -1] = (-qn * u[n + -2] + un) / (qn * y2[(long)(n + -1) + -1] + DAT_00102020);
    while (k = n + -1, 0 < k) {
      y2[(long)k + -1] = y2[(long)k + -1] * y2[(long)n + -1] + u[n + -2];
      n = k;
    }
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}