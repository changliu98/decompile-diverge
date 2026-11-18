double randlc(double *x, double *a) {
  double xn;
  xn = *x * *a;
  *x = xn;
  return (xn * 1.4210854715202E-14);
}