/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double func0(double *xs,int size)

{
  int j_2;
  int j_1;
  int j;
  int i;
  double x_pow;
  double driv;
  double value;
  double ans;
  int size_local;
  double *xs_local;
  
  ans = 0.0;
  value = *xs;
  for (i = 1; i < size; i = i + 1) {
    x_pow = DAT_00102010;
    for (j = 0; j < i; j = j + 1) {
      x_pow = x_pow * 0.0;
    }
    value = xs[i] * x_pow + value;
  }
  while (DAT_00102008 < (double)((ulong)value & _DAT_00102030)) {
    driv = 0.0;
    for (i = 1; i < size; i = i + 1) {
      x_pow = DAT_00102010;
      for (j_1 = 1; j_1 < i; j_1 = j_1 + 1) {
        x_pow = ans * x_pow;
      }
      driv = (double)i * xs[i] * x_pow + driv;
    }
    ans = ans - value / driv;
    value = *xs;
    for (i = 1; i < size; i = i + 1) {
      x_pow = DAT_00102010;
      for (j_2 = 0; j_2 < i; j_2 = j_2 + 1) {
        x_pow = ans * x_pow;
      }
      value = xs[i] * x_pow + value;
    }
  }
  return ans;
}