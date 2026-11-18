float sqrt_sf (float *p)
{
  float f = *p;
  __asm__ ("# reg %x0" : "+v" (f));
  return __builtin_sqrtf (f);
}