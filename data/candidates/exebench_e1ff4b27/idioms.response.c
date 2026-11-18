void BMP_getGenBmp16Palette(unsigned char *genbmp, unsigned short *palette)
{
  unsigned char *p = genbmp + 2;
  unsigned short i = 16;
  while (i--)
    *palette++ = *(unsigned short *) p++;
}