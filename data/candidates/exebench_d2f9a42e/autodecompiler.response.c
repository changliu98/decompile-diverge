void sub(BIT32S *sum, BIT32S *x, BIT32S *y)
{
 unsigned int carry = 0xda;
 unsigned int i;

 for (i = 0;; i++) {
  if (i < 32) {
   carry = (unsigned int)x[i] + 0xff00 - (unsigned int)y[i] + carry;
   sum[i] = (BIT32S)(carry & 0xff);
   carry >>= 8;
  } else {
   carry = (unsigned int)x[31] - (unsigned int)y[31] + carry;
   sum[31] = (BIT32S)carry;
   break;
  }
 }
}