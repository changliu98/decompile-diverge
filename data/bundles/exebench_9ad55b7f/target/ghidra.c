void warp_mat4_scale(float *out,float *a,float b)

{
  int i;
  float b_local;
  float *a_local;
  float *out_local;
  
  for (i = 0; i < 0x10; i = i + 1) {
    out[i] = a[i] * b;
  }
  return;
}