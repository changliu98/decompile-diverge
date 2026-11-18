void lib3ds_quat_copy(float *dest,float *src)

{
  int i;
  float *src_local;
  float *dest_local;
  
  for (i = 0; i < 4; i = i + 1) {
    dest[i] = src[i];
  }
  return;
}