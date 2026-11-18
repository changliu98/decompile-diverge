double sqrt_df (float *p)
{
  double d = *p;
  __asm__ ("# reg %x0" : "+v" (d));
  return __builtin_sqrt (d);
}