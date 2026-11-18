static float *get_positive(float *in, int count, int *out_count)
{
  int i;
  float *out = (float*)malloc(sizeof(float)*count);
  *out_count = 0;
  for (i = 0; i < count; i++)
    if (in[i] > 0.0f)
      out[(*out_count)++] = in[i];
  return out;
}