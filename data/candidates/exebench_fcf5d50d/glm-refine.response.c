void __cdecl mult_add_into_cpu(int N, float *X, float *Y, float *Z)
{
  for (int i = 0; i < N; ++i)
  {
    Z[i] += X[i] * Y[i];
  }
}