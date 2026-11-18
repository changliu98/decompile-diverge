void __cdecl lib3ds_quat_copy(float *dest, float *src)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 4; ++i )
    dest[i] = src[i];
}