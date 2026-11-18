void __cdecl ccp4_dcross(const double *a, const double *b, double *c)
{
  *c = a[1] * b[2] - b[1] * a[2];
  c[1] = a[2] * *b - b[2] * *a;
  c[2] = *a * b[1] - *b * a[1];
}