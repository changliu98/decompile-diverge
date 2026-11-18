static inline float abs_sf(void *ptr)
{
  float *f = (float *)ptr;
  return *f & 0x7fffffff;
}