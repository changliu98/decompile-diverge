void __cdecl warp_mat4_scale(float *out, const float *a, float b)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < 16; ++i )
    out[i] = a[i] * b;
}