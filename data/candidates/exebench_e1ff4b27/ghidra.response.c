void BMP_getGenBmp16Palette(unsigned_short *genbmp16,unsigned_short *pal)

{
  unsigned_short *dst;
  unsigned_short *src;
  unsigned_short i;
  unsigned_short *pal_local;
  unsigned_short *genbmp16_local;
  
  i = 0x10;
  dst = pal;
  src = genbmp16 + 2;
  while (i != 0) {
    *dst = *src;
    dst = dst + 1;
    src = src + 1;
    i = i - 1;
  }
  return;
}