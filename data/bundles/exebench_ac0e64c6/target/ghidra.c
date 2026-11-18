void warp_mat4_add_scaled(float *out,float *a,float *b,float c)

{
  int i;
  float c_local;
  float *b_local;
  float *a_local;
  float *out_local;
  
  for (i = 0; i < 0x10; i = i + 1) {
    out[i] = b[i] * c + a[i];
  }
  return;
}