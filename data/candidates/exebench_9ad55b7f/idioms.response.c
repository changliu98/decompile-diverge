void warp_mat4_scale(float *out, float s, float *in)
{
  int i;
  for (i = 0; i < 16; i++)
    out[i] = s * in[i];
}