void __cdecl mlMatrixTransposeTo(const float *a, float *result)
{
  unsigned int j; // [rsp+0h] [rbp-18h]
  unsigned int i; // [rsp+4h] [rbp-14h]

  for ( j = 0; j < 4; ++j )
  {
    for ( i = 0; i < 4; ++i )
      result[4 * j + i] = a[4 * i + j];
  }
}