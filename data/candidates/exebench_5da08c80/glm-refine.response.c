bool __cdecl mmeq(const float *A, const float *B, size_t rows, size_t cols)
{
  size_t total_elements = rows * cols;

  for (size_t i = 0; i < total_elements; ++i)
  {
    if (A[i] != B[i])
      return false;
  }
  return true;
}