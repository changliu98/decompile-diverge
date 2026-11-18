int UTF8toUnicode(char *str, int *uni, int *len, unsigned long leaveLen)
{
  char c = *str;
  if ( (c & 0xf8) == 0xf0 )
  {
    if ( leaveLen < 4 ||
        (str[1] & 0xc0) != 0x80 ||
        (str[2] & 0xc0) != 0x80 ||
        (str[3] & 0xc0) != 0x80 )
      return 2;
    *len = 4;
    *uni |= c & 0x07;
    *uni <<= 6;
    *uni |= str[1] & 0x3f;
    *uni <<= 6;
    *uni |= str[2] & 0x3f;
    *uni <<= 6;
    *uni |= str[3] & 0x3f;
    return 0;
  }
  if ( (c & 0xf0) == 0xe0 )
  {
    if ( leaveLen < 3 ||
        (str[1] & 0xc0) != 0x80 ||
        (str[2] & 0xc0) != 0x80 )
      return 2;
    *len = 3;
    *uni |= c & 0x0f;
    *uni <<= 6;
    *uni |= str[1] & 0x3f;
    *uni <<= 6;
    *uni |= str[2] & 0x3f;
    return 0;
  }
  if ( (c & 0xe0) == 0xc0 )
  {
    if ( leaveLen < 2 ||
        (str[1] & 0xc0) != 0x80 )
      return 2;
    *len = 2;
    *uni |= c & 0x1f;
    *uni <<= 6;
    *uni |= str[1] & 0x3f;
    return 0;
  }
  if ( (c & 0x80) == 0x00 )
  {
    *len = 1;
    *uni = c;
    return 0;
  }
  return 1;
}