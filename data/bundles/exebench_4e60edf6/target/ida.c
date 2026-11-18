void __cdecl warp_mat4_fill_transpose(float *out, const float *in)
{
  *out = *in;
  out[1] = in[4];
  out[2] = in[8];
  out[3] = in[12];
  out[4] = in[1];
  out[5] = in[5];
  out[6] = in[9];
  out[7] = in[13];
  out[8] = in[2];
  out[9] = in[6];
  out[10] = in[10];
  out[11] = in[14];
  out[12] = in[3];
  out[13] = in[7];
  out[14] = in[11];
  out[15] = in[15];
}