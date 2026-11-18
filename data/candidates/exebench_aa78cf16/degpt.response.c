void vdiff(float *dst,float *a,float *b)

{
  float *b_local;
  float *a_local;
  float *dst_local;
  
  *dst = *a - *b;
  dst[1] = a[1] - b[1];
  dst[2] = a[2] - b[2];
  return;
}