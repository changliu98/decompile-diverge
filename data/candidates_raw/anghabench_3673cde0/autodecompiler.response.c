float my_modff(float x, float *iptr)
{
 union {float f; uint32_t i;} u = {x};
 uint32_t mask;
 int e;

 e = (int)(u.i>>23 & 0xff) - 0x7f;


 if (e >= 24) {
  *iptr = x;
  if (e == 0x80 && u.i<<9 != 0) {
   return x;
  }
  u.i &= 0x80000000;
  return u.f;
 }

 if (e < 0) {
  u.i &= 0x80000000;
  *iptr = u.f;
  return x;
 }

 mask = (1U<<23) >> e;
 if ((u.i & mask) == 0) {
  *iptr = x;
  u.i &= 0x80000000;
  return u.f;
 }
 u.i &= ~mask;
 *iptr = u.f;
 return x - u.f;
}