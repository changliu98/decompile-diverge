float __cdecl dotProduct(float *A, float *B, size_t size)
{
  int i; // [rsp+0h] [rbp-20h]
  float sum; // [rsp+4h] [rbp-1Ch]

  sum = 0.0;
  for ( i = 0; i < size; ++i )
    sum = (float)(A[i] * B[i]) + sum;
  return sum;
}