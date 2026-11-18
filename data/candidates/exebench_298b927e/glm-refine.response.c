float __cdecl FDot(float *vec1, float *vec2, int n)
{
  float result = 0.0f;

  for (int i = 0; i < n; ++i)
  {
    result += vec1[i] * vec2[i];
  }

  return result;
}