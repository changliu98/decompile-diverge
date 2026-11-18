float __cdecl dotProduct(float *A, float *B, size_t size)
{
  float sum = 0.0f;

  for (size_t i = 0; i < size; ++i)
    sum += A[i] * B[i];

  return sum;
}