void __cdecl cross3(double *result, double *a, double *b)
{
  *result = a[1] * b[2] - a[2] * b[1];
  result[1] = a[2] * *b - *a * b[2];
  result[2] = *a * b[1] - a[1] * *b;
}