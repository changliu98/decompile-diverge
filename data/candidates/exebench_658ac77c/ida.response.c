void __cdecl vertexAdd(double *a, double *b, double *out)
{
  *out = *a + *b;
  out[1] = a[1] + b[1];
  out[2] = a[2] + b[2];
}