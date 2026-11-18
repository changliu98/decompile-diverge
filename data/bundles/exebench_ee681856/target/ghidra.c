void c_saxpy(int n,double sa,double *sx,double *sy)

{
  int iVar1;
  int m;
  int i;
  double *sy_local;
  double *sx_local;
  double sa_local;
  int n_local;
  
  if ((0 < n) && ((sa != 0.0 || (NAN(sa))))) {
    iVar1 = n % 4;
    if (iVar1 != 0) {
      for (i = 1; i <= iVar1; i = i + 1) {
        sy[i + -1] = sa * sx[i + -1] + sy[i + -1];
      }
    }
    for (i = iVar1 + 1; i <= n; i = i + 4) {
      sy[i + -1] = sa * sx[i + -1] + sy[i + -1];
      sy[i] = sa * sx[i] + sy[i];
      sy[i + 1] = sa * sx[i + 1] + sy[i + 1];
      sy[i + 2] = sa * sx[i + 2] + sy[i + 2];
    }
  }
  return;
}