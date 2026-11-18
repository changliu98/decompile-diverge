void __cdecl mult_add_into_cpu(int N, float *X, float *Y, float *Z)
{
  int i; // [rsp+0h] [rbp-24h]

  for ( i = 0; i < N; ++i )
    Z[i] = (float)(X[i] * Y[i]) + Z[i];
}