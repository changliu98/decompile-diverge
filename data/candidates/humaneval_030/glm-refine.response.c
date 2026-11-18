float *__cdecl func0(const float *l, int count, int *out_count)
{
  float *out = (float *)malloc(sizeof(float) * count);
  *out_count = 0;
  
  for (int i = 0; i < count; ++i)
  {
    if (l[i] > 0.0f)
    {
      out[(*out_count)++] = l[i];
    }
  }
  
  return out;
}