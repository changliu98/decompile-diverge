void __cdecl mat3mulv(float *const dest, const float *const mat, const float *const v)
{
  int i; // [rsp+0h] [rbp-24h]
  float x; // [rsp+4h] [rbp-20h]
  int k; // [rsp+8h] [rbp-1Ch]

  for ( k = 0; k < 3; ++k )
  {
    x = 0.0;
    for ( i = 0; i < 3; ++i )
      x = (float)(mat[3 * k + i] * v[i]) + x;
    dest[k] = x;
  }
}