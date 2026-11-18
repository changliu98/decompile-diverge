static int set_divisor(int divisor, unsigned int *lcr)
{
 int ret;
 int div;

 switch (divisor) {
 case 1:
  *lcr |= (1 << 23);
  ret = 0;
  break;
 case 3:
  *lcr |= ((1 << 23) | (1 << 20));
  ret = 0;
  break;
 default:
  if (divisor % 2) {
   ret = -1;
  } else {
   div = divisor / 2 - 1;
   if (div == 8 || div == 9) {
    ret = -1;
   } else {
    *lcr |= ((div & 0xf) << 20);
    ret = 0;
   }
  }
 }

 return ret;
}