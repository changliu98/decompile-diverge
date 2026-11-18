void __cdecl geom_matmat2d(const double *a, const double *b, double *c)
{
  *c = *a * *b + a[2] * b[1];
  c[1] = a[1] * *b + a[3] * b[1];
  c[2] = *a * b[2] + a[2] * b[3];
  c[3] = a[1] * b[2] + a[3] * b[3];
}