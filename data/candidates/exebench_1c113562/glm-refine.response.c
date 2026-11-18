void __cdecl fn_5(double *a, double *b, double *sum, double *prod)
{
  for (int i = 0; i < 10; ++i)
  {
    sum[i] = a[i] * b[i];
    prod[i] = a[i] * b[i];
  }
}