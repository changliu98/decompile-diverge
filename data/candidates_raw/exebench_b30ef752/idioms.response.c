void set_value(unsigned short *val, unsigned short min, unsigned short max)
{
  if(*val > max)
    *val = max;
  else if(*val < min)
    *val = min;
}