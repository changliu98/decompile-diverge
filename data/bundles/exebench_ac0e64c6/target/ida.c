void __cdecl warp_mat4_add_scaled(float *out, const float *a, const float *b, float c)
{
  int i; // [rsp+0h] [rbp-20h]

  for ( i = 0; i < 16; ++i )
    out[i] = (float)(b[i] * c) + a[i];
}