void __cdecl geom_cross3d(const double *a, const double *b, double *result)
{
  *result = a[1] * b[2] - a[2] * b[1];
  result[1] = a[2] * *b - *a * b[2];
  result[2] = *a * b[1] - a[1] * *b;
}