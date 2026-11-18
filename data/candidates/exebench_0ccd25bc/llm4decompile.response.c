int
unicoder_utf32_decode(uint32_t *result, const unsigned char *p, int endianness)
{
  uint32_t u;
  int i;

  if (endianness != 2 && endianness != 1)
    return -4;

  if (!p)
    return -1;

  if (!result)
    return -1;

  u = 0;
  for (i = 0; i < 4; i++)
    {
      if (endianness == 2)
        {
          if (i > 0)
            u <<= 8;
          u |= p[i];
        }
      else
        {
          if (i > 0)
            u >>= 8;
          u |= p[i] << 24;
        }
    }

  if (u >= 0x110000)
    return -16;

  if (u >= 0xd800 && u <= 0xdfff)
    return -16;

  *result = u;

  return 4;
}