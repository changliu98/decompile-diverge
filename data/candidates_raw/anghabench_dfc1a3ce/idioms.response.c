void f2le16(float *src, unsigned short *dest)
{
  unsigned int u = *((uint32_t *)src);
  unsigned int mantissa;
  unsigned int remainder;
  unsigned int lsb;
  unsigned int exponent;
  unsigned int sign;
  unsigned char shift;
  if (u >= 0x80000000)
  {
    *dest = 0x7FFF;
  }
  else
  {
    sign = (u & 0x80000000) >> 16;
    if (u >= 0x47800000)
    {
      *dest = (sign | 0x7C00);
    }
    else if (u < 0x33000001)
    {
      *dest = sign;
    }
    else
    {
      exponent = (u >> 23) & 0xFF;
      mantissa = u & 0x7FFFFF;
      if (exponent > 0x70)
      {
        shift = 13;
        exponent -= 112;
      }
      else
      {
        shift = 126 - exponent;
        exponent = 0;
        mantissa |= 0x800000;
      }
      lsb = (1 << shift) >> 1;
      remainder = mantissa & (lsb - 1);
      mantissa >>= shift;
      if (remainder > lsb || (remainder == lsb && (mantissa & 1)))
      {
        mantissa++;
        if (mantissa & 0x3FF)
        {
        }
        else
        {
          exponent++;
          mantissa = 0;
        }
      }
      *dest = (mantissa | (exponent << 10)) | sign;
    }
  }
}