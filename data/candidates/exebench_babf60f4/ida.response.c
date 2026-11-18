void __cdecl matmult(float *A, float *B, float *C)
{
  int k; // [rsp+0h] [rbp-24h]
  int j; // [rsp+4h] [rbp-20h]
  int i; // [rsp+8h] [rbp-1Ch]

  for ( i = 0; i < 4; ++i )
  {
    for ( j = 0; j < 4; ++j )
    {
      C[4 * j + i] = 0.0;
      for ( k = 0; k < 4; ++k )
        C[4 * j + i] = (float)(A[4 * k + i] * B[4 * j + k]) + C[4 * j + i];
    }
  }
}