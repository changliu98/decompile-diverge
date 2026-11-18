void __cdecl mlPointSubTo(const float *a, const float *b, float *result)
{
  for (unsigned int i = 0; i < 3; ++i)
    result[i] = a[i] - b[i];
}