double GO_frexp(double x,int *exp)

{
  double s;
  int n;
  int *exp_local;
  double x_local;
  
  n = 0;
  s = DAT_00102008;
  x_local = x;
  if (x < 0.0) {
    x_local = -x;
    s = DAT_00102010;
  }
  if ((x_local != 0.0) || (NAN(x_local))) {
    for (; DAT_00102008 <= x_local; x_local = DAT_00102018 * x_local) {
      n = n + 1;
    }
    for (; x_local < DAT_00102018; x_local = DAT_00102020 * x_local) {
      n = n + -1;
    }
  }
  *exp = n;
  return x_local * s;
}