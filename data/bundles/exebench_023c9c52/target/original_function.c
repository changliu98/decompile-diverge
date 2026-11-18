static inline int i2s_sf_sclkdiv(int div, int *out)
{
 int d;

 switch(div) {
 case 1: *out |= (8<<20); return 0;
 case 3: *out |= (9<<20); return 0;
 default:
  if (div%2) return -1;
  d = div/2-1;
  if (d == 8 || d == 9) return -1;
  *out |= (((div/2-1)<<20)&(0xF<<20));
  return 0;
 }
}