void sjis2jis(unsigned char *a, unsigned char *b)
{
  unsigned char c = (a[0]<0xa0)*(-0x50)+0x70;
  unsigned char d = (b[0]>0x9f)*0x01 + (b[0]>0x7f)*0x20 + 0x1f;
  a[0] = (a[0]*2 - b[0]) - (b[0]>0x9f);
  b[0] = b[0] - d;
}