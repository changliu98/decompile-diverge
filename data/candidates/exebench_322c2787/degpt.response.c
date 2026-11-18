void vsub(float *src1,float *src2,float *dst)

{
  float *dst_local;
  float *src2_local;
  float *src1_local;
  
  *dst = *src1 - *src2;
  dst[1] = src1[1] - src2[1];
  dst[2] = src1[2] - src2[2];
  return;
}