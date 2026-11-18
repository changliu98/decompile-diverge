void mlMatrixAddTo(float *a, float *b, float *c)
{
#pragma omp parallel for simd schedule(static) collapse(1)
  for (unsigned int i = 0; i < 16; ++i) {
    c[i] = a[i] + b[i];
  }
}