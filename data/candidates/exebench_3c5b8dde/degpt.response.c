void mat3d_from_mat3f(double *dest,float *src)

{
  int i;
  float *src_local;
  double *dest_local;
  
  for (i = 0; i < 9; i = i + 1) {
    dest[i] = (double)src[i];
  }
  return;
}