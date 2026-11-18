int dspline(double *x, double *y, int n, int if1, double cond1, int ifn, double condn, double *y2)
{
  int i__1;
  int i__; int k;
  double sig; double p;
  double u[2000];
  double y2a; double ya; double y1; double y2a1; double y1a;
  int na; int if1a; int ifna;
  double cond1a; double condna;
  na = n;
  if1a = if1;
  cond1a = cond1;
  ifna = ifn;
  condna = condn;
  --y2;
  --y;
  --x;
  if (na > 2000) {
    return 1;
  }
  if (if1a == 2) {
    y2[1] = 0.f;
    u[0] = cond1a;
  } else {
    if (if1a != 1) {
      return 2;
    }
    y2[1] = -0.5f;
    u[0] = (y[2] - y[1]) / (x[2] - x[1]) * (2.f / (x[2] - x[1])
     - cond1a);
  }
  i__1 = na - 1;
  for (i__ = 2; i__ <= i__1; ++i__) {
    sig = (x[i__] - x[i__ - 1]) / (x[i__ + 1] - x[i__ - 1]);
    p = (sig * y2[i__ - 1] + 2.f);
    y2[i__] = (sig - 1.f) / p;
    u[i__ - 1] = (sig * u[i__ - 2] + 6.f
     * (y[i__ + 1] - y[i__]) / (x[i__ + 1] - x[i__])
     - 6.f * (y[i__] - y[i__ - 1]) / (x[i__] - x[i__ - 1])
     ) / p;
  }
  if (ifna == 2) {
    y2a = 0.f;
    u[na - 1] = condna;
  } else {
    if (ifna != 1) {
      return 3;
    }
    y2a = 0.5f;
    u[na - 1] = (condna - (y[na] - y[na - 1]) / (x[na] - x[na - 1]))
     * (2.f / (x[na] - x[na - 1]));
  }
  y2[na] = (y2a * u[na - 2] + u[na - 1]) / (y2a * y2[na - 1] + 1.f);
  for (k = na - 1; k >= 1; --k) {
    y2[k] = y2[k] * y2[k + 1] + u[k - 1];
  }
  return 0;
}