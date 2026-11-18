void swap_float_4(float *tnf4)

{
  int *tni4;
  float *tnf4_local;
  
  *tnf4 = (float)((int)*tnf4 >> 0x18 & 0xffU | (int)*tnf4 << 0x18 | (int)*tnf4 >> 8 & 0xff00U |
                 ((uint)*tnf4 & 0xff00) << 8);
  return;
}