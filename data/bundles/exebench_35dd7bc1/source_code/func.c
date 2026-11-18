
static inline int i2s_sf_mclkdiv(int div, int *out)
{
 int d;

 switch(div) {
 case 1: *out |= (0x14<<24); return 0;
 case 3: *out |= (0x13<<24); return 0;
 case 5: *out |= (0x12<<24); return 0;
 case 14: *out |= (0x0E<<24); return 0;
 default:
  if (div%2) return -1;
  d = div/2-1;
  if (d == 0x14 || d == 0x13 || d == 0x12 || d == 0x0E)
   return -1;
  *out |= (((div/2-1)<<24)&(0x1F<<24));
  return 0;
 }
}
