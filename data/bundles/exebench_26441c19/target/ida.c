int __cdecl Utf8ToUnicode(char *utf8char, int *unicode, int *len, int leaveLen)
{
  char cTmp; // [rsp+1h] [rbp-25h]

  cTmp = *utf8char;
  if ( (*utf8char & 0xF8) != 240 )
  {
    if ( (cTmp & 0xF0) == 224 )
    {
      if ( leaveLen < 3 || (utf8char[1] & 0xC0) != 128 || (utf8char[2] & 0xC0) != 128 )
        return 2;
      *len = 3;
      *unicode |= cTmp & 0xF;
      *unicode <<= 6;
      *unicode |= utf8char[1] & 0x3F;
      *unicode <<= 6;
      *unicode |= utf8char[2] & 0x3F;
    }
    else if ( (cTmp & 0xE0) == 192 )
    {
      if ( leaveLen < 2 || (utf8char[1] & 0xC0) != 128 )
        return 2;
      *len = 2;
      *unicode |= cTmp & 0x1F;
      *unicode <<= 6;
      *unicode |= utf8char[1] & 0x3F;
    }
    else
    {
      if ( (cTmp & 0x80) != 0 )
        return 1;
      *len = 1;
      *unicode = cTmp;
    }
    return 0;
  }
  if ( leaveLen >= 4 && (utf8char[1] & 0xC0) == 128 && (utf8char[2] & 0xC0) == 128 && (utf8char[3] & 0xC0) == 128 )
  {
    *len = 4;
    *unicode |= cTmp & 7;
    *unicode <<= 6;
    *unicode |= utf8char[1] & 0x3F;
    *unicode <<= 6;
    *unicode |= utf8char[2] & 0x3F;
    *unicode <<= 6;
    *unicode |= utf8char[3] & 0x3F;
    return 0;
  }
  return 2;
}