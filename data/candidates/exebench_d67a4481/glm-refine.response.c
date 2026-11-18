int __cdecl Utf8ToUnicode(char *utf8char, int *unicode, int *len, size_t leaveLen)
{
  char cTmp = *utf8char;

  // 4-byte sequence: 11110xxx
  if ( (cTmp & 0xF8) == 0xF0 )
  {
    if ( leaveLen < 4 || !IS_UTF8_CONT(utf8char[1]) || !IS_UTF8_CONT(utf8char[2]) || !IS_UTF8_CONT(utf8char[3]) )
      return 2;
    
    *len = 4;
    *unicode |= cTmp & 0x07;
    *unicode <<= 6;
    *unicode |= utf8char[1] & 0x3F;
    *unicode <<= 6;
    *unicode |= utf8char[2] & 0x3F;
    *unicode <<= 6;
    *unicode |= utf8char[3] & 0x3F;
    return 0;
  }

  // 3-byte sequence: 1110xxxx
  if ( (cTmp & 0xF0) == 0xE0 )
  {
    if ( leaveLen < 3 || !IS_UTF8_CONT(utf8char[1]) || !IS_UTF8_CONT(utf8char[2]) )
      return 2;
    
    *len = 3;
    *unicode |= cTmp & 0x0F;
    *unicode <<= 6;
    *unicode |= utf8char[1] & 0x3F;
    *unicode <<= 6;
    *unicode |= utf8char[2] & 0x3F;
    return 0;
  }

  // 2-byte sequence: 110xxxxx
  if ( (cTmp & 0xE0) == 0xC0 )
  {
    if ( leaveLen < 2 || !IS_UTF8_CONT(utf8char[1]) )
      return 2;
    
    *len = 2;
    *unicode |= cTmp & 0x1F;
    *unicode <<= 6;
    *unicode |= utf8char[1] & 0x3F;
    return 0;
  }

  // 1-byte sequence: 0xxxxxxx
  if ( (cTmp & 0x80) != 0 )
    return 1; // Invalid leading byte (10xxxxxx or 11111xxx)

  *len = 1;
  *unicode = cTmp;
  return 0;
}