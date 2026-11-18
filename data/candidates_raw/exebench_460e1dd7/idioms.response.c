void swap_int(unsigned int *val)
{
  unsigned int tmp;
  tmp = (*val & 0xff000000) >> 24;
  tmp += (*val & 0x00ff0000) >> 8;
  tmp += (*val & 0x0000ff00) << 8;
  tmp += (*val & 0x000000ff) << 24;
  *val = tmp;
}