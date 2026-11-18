double **__cdecl AcquireBilateralTLS(const size_t number_threads, const size_t width, const size_t height)
{
  double **weights;

  // Allocate an array of pointers for each thread, plus 1 extra (likely for a global/shared context)
  weights = (double **)AcquireQuantumMemory(number_threads + 1, sizeof(double *));
  if (!weights)
    return NULL;

  // Initialize the thread pointer array to NULL
  memset(weights, 0, number_threads * sizeof(double *));

  // Allocate a 2D weight buffer (width * height) for each thread context
  for (ssize_t i = 0; i <= number_threads; ++i)
  {
    weights[i] = (double *)AcquireQuantumMemory(width, height * sizeof(double));
    if (!weights[i])
      return DestroyBilateralTLS(number_threads, weights);
  }

  return weights;
}