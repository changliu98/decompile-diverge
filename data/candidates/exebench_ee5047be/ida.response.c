void __cdecl geom_matvec2d(const double *m, const double *x, double *y)
{
  *y = *m * *x + m[2] * x[1];
  y[1] = m[1] * *x + m[3] * x[1];
}