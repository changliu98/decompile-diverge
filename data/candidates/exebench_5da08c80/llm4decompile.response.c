int mmeq(float* A, float* B, size_t rows, size_t cols)
{
  int i;
  for (i = 0; i < rows*cols; i++)
    if (A[i] != B[i] || A[i] != A[i] || B[i] != B[i])
      return 0;
  return 1;
}