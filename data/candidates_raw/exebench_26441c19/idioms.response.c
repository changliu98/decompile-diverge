int UTF8toUnicode(char *utf8char, int *unicode, int *len, int leaveLen)
{
  char cTmp = *utf8char;
  if ( (cTmp & 0xf8) == 0xf0 )
  {
    if ( leaveLen < 4 ||
         (utf8char[1] & 0xc0) != 0x80 ||
         (utf8char[2] & 0xc0) != 0x80 ||
         (utf8char[3] & 0xc0) != 0x80 )
      return 2;
    *len = 4;
    *unicode |= cTmp & 0x07;
    *unicode <<= 6;
    *unicode |= utf8char[1] & 0x3f;
    *unicode <<= 6;
    *unicode |= utf8char[2] & 0x3f;
    *unicode <<= 6;
    *unicode |= utf8char[3] & 0x3f;
    return 0;
  }
  if ( (cTmp & 0xf0) == 0xe0 )
  {
    if ( leaveLen < 3 ||
         (utf8char[1] & 0xc0) != 0x80 ||
         (utf8char[2] & 0xc0) != 0x80 )
      return 2;
    *len = 3;
    *unicode |= cTmp & 0x0f;
    *unicode <<= 6;
    *unicode |= utf8char[1] & 0x3f;
    *unicode <<= 6;
    *unicode |= utf8char[2] & 0x3f;
  }
  else if ( (cTmp & 0xe0) == 0xc0 )
  {
    if ( leaveLen < 2 ||
         (utf8char[1] & 0xc0) != 0x80 )
      return 2;
    *len = 2;
    *unicode |= cTmp & 0x1f;
    *unicode <<= 6;
    *unicode |= utf8char[1] & 0x3f;
  }
  else if ( (cTmp & 0x80) == 0x00 )
  {
    *len = 1;
    *unicode = cTmp & 0xff;
  }
  else
    return 1;
  return 0;
}