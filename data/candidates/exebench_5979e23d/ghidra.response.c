void vscale(float *dst,float *src,float scale)

{
  float scale_local;
  float *src_local;
  float *dst_local;
  
  *dst = *src * scale;
  dst[1] = src[1] * scale;
  dst[2] = src[2] * scale;
  return;
}