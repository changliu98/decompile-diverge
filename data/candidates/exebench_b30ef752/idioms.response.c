void limit2_u16(unsigned short *val, unsigned short min, unsigned short max)
{
  if(*val > max)
    *val = max;
  else if(*val < min)
    *val = min;
}