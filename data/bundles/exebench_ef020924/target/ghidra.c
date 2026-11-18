void swapfloat(float *flt)

{
  int *ff;
  float *flt_local;
  
  *flt = (float)((int)*flt << 0x18 | ((uint)*flt & 0xff00) << 8 | ((uint)*flt & 0xff0000) >> 8 |
                (uint)*flt >> 0x18);
  return;
}