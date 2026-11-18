void mul_int(int factor1, int factor2, int *product)
{
  double dAccum = (double)factor1 * (double)factor2;
  product[0] = (int)(dAccum & 0x7fffffff);
  if (dAccum < 0)
    product[1] = (int)((dAccum - (double)0x80000000) / (double)0x80000000);
  else
    product[1] = (int)((dAccum + (double)0x80000000) / (double)0x80000000);
}