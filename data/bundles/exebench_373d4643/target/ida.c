void __cdecl lib3ds_vector_copy(float *dst, float *src)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 3; ++i )
    dst[i] = src[i];
}