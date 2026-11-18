void __cdecl geom_matTvec2d(const double *m, const double *x, double *y)
{
  *y = *m * *x + m[1] * x[1];
  y[1] = m[2] * *x + m[3] * x[1];
}