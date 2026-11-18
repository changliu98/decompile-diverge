static int set_divisor(int divisor, unsigned int *regs)
{
 int ret;
 int div;

 switch (divisor) {
 case 1:
  regs[0] |= (20 << 24);
  ret = 0;
  break;
 case 3:
  regs[0] |= (19 << 24);
  ret = 0;
  break;
 case 5:
  regs[0] |= (18 << 24);
  ret = 0;
  break;
 case 14:
  regs[0] |= (14 << 24);
  ret = 0;
  break;
 default:
  if (divisor % 2) {
   ret = -1;
   break;
  }
  div = divisor / 2 - 1;
  if ((div == 20) || (div == 19) || (div == 18) || (div == 14)) {
   ret = -1;
   break;
  }
  regs[0] |= ((div & 0x1f) << 24);
  ret = 0;
 }

 return ret;
}