double frexp(double x,int *exp)

{
  double sig;
  int e;
  int sign;
  int *exp_local;
  double x_local;
  
  sign = 1;
  if (0.0 <= x) {
    x_local = x;
    if ((x == 0.0) && (!NAN(x))) {
      *exp = 0;
      return 0.0;
    }
  }
  else {
    sign = -1;
    x_local = x * -1.0;
  }
  *exp = 0;
  e = 1;
  sig = x_local;
  while (sig < DAT_00102008 || DAT_00102010 <= sig) {
    e = e << 1;
    *exp = *exp + 1;
    sig = x_local / (double)e;
  }
  return sig * (double)sign;
}