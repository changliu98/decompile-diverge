void utf8_encode(int ucs, char *utf8)
{
  int len = 0;
  if (ucs < 0x00000080)
  {
    utf8[len++] = (ucs & 0x7f);
  }
  else if (ucs < 0x00000800)
  {
    utf8[len++] = (ucs & 0x0000003f) | 0x80;
    utf8[len++] = (ucs & 0x00007c00) >> 6 | 0x80;
    utf8[len++] = (ucs & 0x0007c000) >> 12 | 0x80;
    utf8[len++] = (ucs & 0x007f0000) >> 18 | 0xc0;
  }
  else if (ucs < 0x00010000)
  {
    utf8[len++] = (ucs & 0x0000003f) | 0x80;
    utf8[len++] = (ucs & 0x000007c0) >> 6 | 0x80;
    utf8[len++] = (ucs & 0x00007c00) >> 12 | 0x80;
    utf8[len++] = (ucs & 0x0007c000) >> 18 | 0xe0;
  }
  else if (ucs < 0x10ffff)
  {
    utf8[len++] = (ucs & 0x0000003f) | 0x80;
    utf8[len++] = (ucs & 0x000007c0) >> 6 | 0x80;
    utf8[len++] = (ucs & 0x00007c00) >> 12 | 0x80;
    utf8[len++] = (ucs & 0x0007c000) >> 18 | 0xf0;
  }
  utf8[len] = '\0';
}