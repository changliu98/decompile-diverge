void __cdecl myGlMultMatrix(const float *a, const float *b, float *out)
{
  int j; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]

  for ( i = 0; i < 4; ++i )
  {
    for ( j = 0; j < 4; ++j )
      out[4 * i + j] = (float)(a[4 * i + 3] * b[j + 12])
                     + (float)((float)(a[4 * i + 2] * b[j + 8])
                             + (float)((float)(a[4 * i] * b[j]) + (float)(a[4 * i + 1] * b[j + 4])));
  }
}