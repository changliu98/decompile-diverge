int dspline(double *x, double *y, int n, int ib, double b, int ie, double e,
            double *y2) {
  int i, nmax;
  double sig, p, qn, un, u[2000];
  double *y2a, *ya, *xa;
  nmax = n;
  y2a = y2 - 1;
  ya = y - 1;
  xa = x - 1;
  if (nmax > 2000) return 1;
  if (ib == 2) {
    y2a[1] = 0.0;
    u[0] = b;
  } else if (ib == 1) {
    y2a[1] = -0.5;
    u[0] = (3.0 / (xa[2] - xa[1]) * ((ya[2] - ya[1]) / (xa[2] - xa[1]) - b));
  } else
    return 2;
  for (i = 2; i <= nmax - 1; i++) {
    sig = (xa[i] - xa[i - 1]) / (xa[i + 1] - xa[i - 1]);
    p = 2.0 + sig * y2a[i - 1];
    y2a[i] = (sig - 1.0) / p;
    qn = (ya[i + 1] - ya[i]) / (xa[i + 1] - xa[i]) -
         (ya[i] - ya[i - 1]) / (xa[i] - xa[i - 1]);
    u[i - 1] = (qn * 6.0 / (xa[i + 1] - xa[i - 1]) - sig * u[i - 2]) / p;
  }
  if (ie == 2) {
    un = 0.0;
    qn = e;
  } else if (ie == 1) {
    un = 0.5;
    qn = (3.0 / (xa[nmax] - xa[nmax - 1]) *
          (e - (ya[nmax] - ya[nmax - 1]) / (xa[nmax] - xa[nmax - 1])));
  } else
    return 3;
  y2a[nmax] = (qn - un * u[nmax - 2]) / (1.0 + un * y2a[nmax - 1]);
  for (i = nmax - 1; i >= 1; i--) y2a[i] = y2a[i] * y2a[i + 1] + u[i - 1];
  return 0;
}