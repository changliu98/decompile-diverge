float modff(float x, float *iptr)
{
 int lx,ix;
 lx = ((*(int*)&x)>>23 & 0xff) - 0x7f;
 ix = *(int*)&x;
 if(lx >= 23) {
     *iptr = x;
     if(lx == 0x80 && ((ix & 0x7fffff) != 0))
  return x;
     ix &= 0x80000000;
     return *(float*)&ix;
 }
 if(lx < 0) {
     ix &= 0x80000000;
     *iptr = *(float*)&ix;
     return x;
 }
 ix &= 0x7fffff>>lx;
 if(ix == 0) {
     *iptr = x;
     ix = *(int*)&x;
     ix &= 0x80000000;
     return *(float*)&ix;
 }
 ix = *(int*)&x;
 ix &= ~(0x7fffff>>lx);
 *iptr = *(float*)&ix;
 return x - *(float*)&ix;
}