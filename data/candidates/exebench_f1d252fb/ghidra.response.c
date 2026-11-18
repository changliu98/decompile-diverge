void endian_swap16bit(unsigned_short *x)

{
  unsigned_short *x_local;
  
  *x = *x >> 8 | *x << 8;
  return;
}