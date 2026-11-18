void __cdecl mlPointAddTo(const float *a, const float *b, float *result)
{
  result[0] = a[0] + b[0];
  result[1] = a[1] + b[1];
  result[2] = a[2] + b[2];
}