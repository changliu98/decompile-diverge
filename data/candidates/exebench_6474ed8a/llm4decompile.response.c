int gen256(unsigned char *dst, unsigned prim_poly)
{
  int i;
  unsigned v;

  if (prim_poly & 0x100)
  {
    dst[0] = 0;
    dst[1] = 1;
    v = 1;
    for (i = 2; i < 256; i++)
    {
      v <<= 1;
      if (v & 0x100)
        v = (v & 0xff) ^ (prim_poly & 0xff);
      dst[i] = v & 0xff;
    }
    return 0;
  }
  return -1;
}