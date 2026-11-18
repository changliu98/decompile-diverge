void warp_mat4_add_scaled(float *out, float *in, float *in2, float scale)
{
  int i;
  for (i = 0; i < 16; i++)
    out[i] = in[i] + in2[i] * scale;
}