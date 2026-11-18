void __cdecl multiply_naive(const float *A, const float *B, float *result)
{
  int j; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]

  for ( i = 0; i < 16; i += 4 )
  {
    for ( j = 0; j < 4; ++j )
      result[j + i] = (float)(B[i + 3] * A[j + 12])
                    + (float)((float)(B[i + 2] * A[j + 8]) + (float)((float)(B[i] * A[j]) + (float)(B[i + 1] * A[j + 4])));
  }
}