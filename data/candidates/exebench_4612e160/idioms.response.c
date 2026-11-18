static unsigned int utf8_decode_v2(char *utf8char, unsigned long len, unsigned long *charlen)
{
  if (len == 0 || *utf8char == '\0')
  {
    if (charlen)
      *charlen = 0;
    return (0xffffffff);
  }
  if ((*utf8char & 0x80) == 0)
  {
    if (charlen)
      *charlen = 1;
    return (*utf8char & 0x7f);
  }
  if (((*utf8char & 0xe0) == 0xc0))
  {
    if (charlen)
      *charlen = 2;
    if (len < 2 || *(utf8char + 1) == '\0')
      return (0xffffffff);
    return ((utf8char[1] & 0x3f) |
     ((utf8char[0] & 0x1f) << 6));
  }
  if (((*utf8char & 0xf0) == 0xe0))
  {
    if (charlen)
      *charlen = 3;
    if (len < 3 || *(utf8char + 1) == '\0' || *(utf8char + 2) == '\0')
      return (0xffffffff);
    return ((utf8char[2] & 0x3f) |
     ((utf8char[1] & 0x3f) << 6) |
     ((utf8char[0] & 0x0f) << 12));
  }
  if (((*utf8char & 0xf8) == 0xf0))
  {
    if (charlen)
      *charlen = 4;
    if (len < 4 || *(utf8char + 1) == '\0' ||
        *(utf8char + 2) == '\0' || *(utf8char + 3) == '\0')
      return (0xffffffff);
    return ((utf8char[3] & 0x3f) |
     ((utf8char[2] & 0x3f) << 6) |
     ((utf8char[1] & 0x3f) << 12) |
     ((utf8char[0] & 0x07) << 15));
  }
  if (charlen)
    *charlen = 0;
  return (0xffffffff);
}