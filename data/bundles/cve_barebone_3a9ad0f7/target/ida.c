double **__cdecl AcquireBilateralTLS(const size_t number_threads, const size_t width, const size_t height)
{
  ssize_t i; // [rsp+0h] [rbp-30h]
  double **weights; // [rsp+8h] [rbp-28h]

  weights = (double **)AcquireQuantumMemory(number_threads + 1, 8uLL);
  if ( !weights )
    return 0LL;
  memset(weights, 0, 8 * number_threads);
  for ( i = 0LL; i <= (__int64)number_threads; ++i )
  {
    weights[i] = (double *)AcquireQuantumMemory(width, 8 * height);
    if ( !weights[i] )
      return DestroyBilateralTLS(number_threads, weights);
  }
  return weights;
}