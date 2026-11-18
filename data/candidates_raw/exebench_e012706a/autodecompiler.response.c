void
set_FT(double *ft, double *f, double *t, double *T)
{
 int i;
 for (i = 0; i < 4; i++) {
  f[i] = ft[3 * i + 0];
  t[i] = ft[3 * i + 1];
  T[i] = ft[3 * i + 2];
 }
}