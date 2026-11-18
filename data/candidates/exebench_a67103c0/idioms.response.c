int unicoder_utf16_decode(unsigned int *out, unsigned char *in, int endianness)
{
  if (endianness != 2 && endianness != 1)
    return -4;
  if (in == ((void *)0))
    return -1;
  if (out == ((void *)0))
    return -1;
  unsigned int dbyteA;
  unsigned int dbyteB;
  if (endianness == 1)
  {
    dbyteA = (in[0] << 8) | in[1];
    dbyteB = (in[2] << 8) | in[3];
  }
  else
  {
    dbyteA = in[0] | (in[1] << 8);
    dbyteB = in[2] | (in[3] << 8);
  }
  if (dbyteA >= 0xD800 && dbyteA <= 0xDFFF)
  {
    if (dbyteA <= 0xDBFF && dbyteB >= 0xDC00 && dbyteB <= 0xDFFF)
    {
      *out = 0;
      *out |= dbyteA & 0x03FF;
      *out <<= 10;
      *out |= dbyteB & 0x03FF;
      *out += 0x10000;
      return 4;
    }
    return -8;
  }
  if (dbyteA > 0x10FFFF)
    return -16;
  *out = dbyteA;
  return 2;
}