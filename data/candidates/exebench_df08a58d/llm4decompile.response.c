float abs_sf(float *p)
{
  float_t f;
  f.f = *p;
  f.i &= 0x7fffffff;
  return f.f;
}