void splini(double *xa,double *ya,double *y2a,int n,double x,double *y)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double b2;
  double a2;
  double b;
  double a;
  double h;
  double xx;
  int khi;
  int klo;
  double yi;
  double *y_local;
  double x_local;
  int n_local;
  double *y2a_local;
  double *ya_local;
  double *xa_local;
  
  yi = 0.0;
  klo = 0;
  for (khi = 1; (xa[klo] <= x && x != xa[klo]) && khi < n; khi = khi + 1) {
    xx = x;
    if ((khi < n + -1) && (xa[khi] <= x)) {
      xx = xa[khi];
    }
    dVar1 = xa[khi] - xa[klo];
    dVar2 = (xa[khi] - xx) / dVar1;
    dVar3 = (xx - xa[klo]) / dVar1;
    dVar2 = dVar2 * dVar2;
    dVar3 = dVar3 * dVar3;
    yi = (((DAT_00102020 - dVar2) * ya[klo]) / DAT_00102010 + (dVar3 * ya[khi]) / DAT_00102010 +
         (((-(dVar2 * dVar2 + DAT_00102020) / DAT_00102018 + dVar2 / DAT_00102010) * y2a[klo] +
          ((dVar3 * dVar3) / DAT_00102018 - dVar3 / DAT_00102010) * y2a[khi]) * dVar1 * dVar1) /
         DAT_00102008) * dVar1 + yi;
    klo = klo + 1;
  }
  *y = yi;
  return;
}