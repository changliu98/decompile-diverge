void __cdecl lib3ds_quat_copy(float *dest, float *src)
{
  for (int i = 0; i < 4; ++i)
    dest[i] = src[i];
}