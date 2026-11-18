void c_saxpy(int n, double sa, double *sx, double *sy)
{
  int i; int i4;
  if (n > 0 && sa != 0.0) {
    i4 = n % 4;
    if (i4 > 0) {
      for (i = 1; i <= i4; ++i)
        sy[i - 1] += sa * sx[i - 1];
    }
    for (i = i4 + 1; i <= n; i = i + 4) {
      sy[i - 1] += sa * sx[i - 1];
      sy[i] += sa * sx[i];
      sy[i + 1] += sa * sx[i + 1];
      sy[i + 2] += sa * sx[i + 2];
    }
  }
}