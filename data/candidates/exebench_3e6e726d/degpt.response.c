void mat3f_from_mat3d(float *dest,double *src)

{
  int i;
  double *src_local;
  float *dest_local;
  
  for (i = 0; i < 9; i = i + 1) {
    dest[i] = (float)src[i];
  }
  return;
}