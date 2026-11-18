int _safe_calloc_check_mul(unsigned long a, unsigned long b, unsigned long *res)
{
  unsigned long tmp;
  unsigned long *res2 = res ? res : &tmp;
  *res2 = a * b;
  return (unsigned long)(a * b) >> 64 == 0;
}