void __cdecl mlVectorScaleTo(const float *a, float b, float *result)
{
  result[0] = a[0] * b;
  result[1] = a[1] * b;
  result[2] = a[2] * b;
}