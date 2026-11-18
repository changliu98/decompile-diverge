void lib3ds_vector_copy(float *dst,float *src)

{
  int i;
  float *src_local;
  float *dst_local;
  
  for (i = 0; i < 3; i = i + 1) {
    dst[i] = src[i];
  }
  return;
}