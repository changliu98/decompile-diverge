void
unscale (double *p, unsigned int n)
{
  unsigned int i;
#pragma omp target map(to:p[:n])
#pragma omp parallel for simd schedule(static, 32)
  for (i = 0; i < n; i++)
    p[i] *= 256.0;
}