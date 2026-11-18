void __cdecl cross3(const double *a, const double *b, double *c)
{
  *c = a[1] * b[2] - a[2] * b[1];
  c[1] = a[2] * *b - *a * b[2];
  c[2] = *a * b[1] - a[1] * *b;
}