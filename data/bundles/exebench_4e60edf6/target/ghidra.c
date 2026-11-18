void warp_mat4_fill_transpose(float *out,float *in)

{
  float *in_local;
  float *out_local;
  
  *out = *in;
  out[1] = in[4];
  out[2] = in[8];
  out[3] = in[0xc];
  out[4] = in[1];
  out[5] = in[5];
  out[6] = in[9];
  out[7] = in[0xd];
  out[8] = in[2];
  out[9] = in[6];
  out[10] = in[10];
  out[0xb] = in[0xe];
  out[0xc] = in[3];
  out[0xd] = in[7];
  out[0xe] = in[0xb];
  out[0xf] = in[0xf];
  return;
}