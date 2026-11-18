uint32_t denormal_addf1(uint32_t ix, uint32_t iy)
{
 int exp;
 uint32_t frac;


 if (ix < 0x800000)
  return ix + iy;

 exp = (ix & 0x7F800000) >> 23;


 if (--exp < 0)
  return ix;


 if ((frac = iy >> exp) == 0)
  return ix;


 frac += (ix & 0x7FFFFF) | 0x800000;


 if (frac >= 0x1000000) {
  frac >>= 1;
  exp++;
 }

 return (exp << 23) | (frac & 0x7FFFFF);
}