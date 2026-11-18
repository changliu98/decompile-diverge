int
mulv(Vlong a, Vlong b, Vlong *hi)
{
 ulong ahi, alo, bhi, blo;
 ulong x;
 Vlong v;

 ahi = a.hi;
 alo = a.lo;
 if(hi) {
  v.hi = ahi;
  v.lo = 0;
  *hi = v;
 }
 bhi = b.hi;
 blo = b.lo;
 if(hi) {
  v.hi = bhi;
  v.lo = 0;
  *hi = v;
 }
 x = ahi*blo + alo*bhi;
 if(x >= 0x80000000)
  return 1;
 v.hi = ahi*bhi + (x>>31);
 v.lo = alo*blo;
 if(x & 0x80000000)
  v.hi--;
 if(hi) {
  v.lo |= x<<31;
  *hi = v;
 }
 return 0;
}