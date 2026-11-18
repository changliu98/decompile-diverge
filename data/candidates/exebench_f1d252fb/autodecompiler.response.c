void endian_swap16bit(short *s)
{
  *s = (((*s) & 0xff) << 8) | (((*s) >> 8) & 0xff);
}