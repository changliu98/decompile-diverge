void __cdecl mlVectorDotProductTo(const float *a, const float *b, float *result)
{
  *result = (float)(a[2] * b[2]) + (float)((float)(*a * *b) + (float)(a[1] * b[1]));
}