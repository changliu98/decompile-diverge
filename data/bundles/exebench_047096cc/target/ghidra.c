void endian_swap32bit(uint *x)

{
  uint *x_local;
  
  *x = *x >> 0x18 | (*x & 0xff00) << 8 | *x >> 8 & 0xff00 | *x << 0x18;
  return;
}