void lib3ds_quat_copy(float *dest, float *src)
{
  int i;
  for (i = 0; i < 4; i++)
    dest[i] = src[i];
}