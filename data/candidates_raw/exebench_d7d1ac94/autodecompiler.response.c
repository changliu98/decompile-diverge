int
mulll (long long *p)
{
  int ret = __builtin_mul_overflow (*p, *p, p);
  return ret;
}