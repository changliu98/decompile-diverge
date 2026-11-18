void mov_s(void *src, void *dest)
{
  float *s = (const float *)src;
  float *d = (float *)dest;
  *d = *s;
}