static inline float rarch_get_float1(void *ptr)
{
  float *f = (float *)ptr;
  return *f & 0x7fffffff;
}