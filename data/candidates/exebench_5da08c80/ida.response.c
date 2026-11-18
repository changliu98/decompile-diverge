bool __cdecl mmeq(float *A, float *B, size_t rows, size_t cols)
{
  int i; // [rsp+0h] [rbp-2Ch]

  for ( i = 0; i < cols * rows; ++i )
  {
    if ( A[i] != B[i] )
      return 0;
  }
  return 1;
}