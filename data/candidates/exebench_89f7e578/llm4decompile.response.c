void put_num(unsigned short *dst, unsigned int num, unsigned char len)
{
 if (len > 4)
  *dst++ = 0x2100 | ((num / 10000) % 10) + 0x10;
 if (len > 3)
  *dst++ = 0x2100 | ((num / 1000) % 10) + 0x10;
 if (len > 2)
  *dst++ = 0x2100 | ((num / 100) % 10) + 0x10;
 if (len > 1)
  *dst++ = 0x2100 | ((num / 10) % 10) + 0x10;
 if (len > 0)
  *dst++ = 0x2100 | ((num / 1) % 10) + 0x10;
}