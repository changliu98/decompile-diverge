void __cdecl mlPointSubTo(const float *a, const float *b, float *result)
{
  unsigned int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < 3; ++i )
    result[i] = a[i] - b[i];
}