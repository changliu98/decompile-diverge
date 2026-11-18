int imath_mul_u64(unsigned long a, unsigned long b, unsigned long *res)
{
  unsigned long tmp;
  unsigned long *res2 = res ? res : &tmp;
  *res2 = a * b;
  return (unsigned long)(a * b) >> 64 == 0;
}