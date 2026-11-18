void __cdecl add3(double *a, double *b)
{
  *b = *a + *b;
  b[1] = a[1] + b[1];
  b[2] = a[2] + b[2];
}