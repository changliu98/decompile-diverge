void __cdecl cpy3(double *a, double *b)
{
  *b = *a;
  b[1] = a[1];
  b[2] = a[2];
}