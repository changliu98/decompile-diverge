void scale_mat4(float *out, float s, float *in)
{
  int i;
  for (i = 0; i < 16; i++)
    out[i] = s * in[i];
}