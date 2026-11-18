void BMP_getGenBmp16Palette(unsigned char *pBmp, unsigned short *pPalette) {
  unsigned short i;
  unsigned short *p;
  p = (unsigned short *)pBmp;
  p += 2;
  i = 16;
  while (i--) {
    *pPalette++ = *p++;
  }
}