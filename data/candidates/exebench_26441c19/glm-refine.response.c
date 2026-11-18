int __cdecl Utf8ToUnicode(char *utf8char, int *unicode, int *len, int leaveLen)
{
  unsigned char c = (unsigned char)*utf8char;

  // 4-byte sequence: 11110xxx
  if ((c & 0xF8) == 0xF0)
  {
    if (leaveLen < 4 || 
        (utf8char[1] & 0xC0) != 0x80 || 
        (utf8char[2] & 0xC0) != 0x80 || 
        (utf8char[3] & 0xC0) != 0x80)
    {
      return 2; // Truncated or invalid continuation
    }

    *len = 4;
    *unicode = (c & 0x07);
    *unicode = (*unicode << 6) | (utf8char[1] & 0x3F);
    *unicode = (*unicode << 6) | (utf8char[2] & 0x3F);
    *unicode = (*unicode << 6) | (utf8char[3] & 0x3F);
    return 0;
  }

  // 3-byte sequence: 1110xxxx
  if ((c & 0xF0) == 0xE0)
  {
    if (leaveLen < 3 || 
        (utf8char[1] & 0xC0) != 0x80 || 
        (utf8char[2] & 0xC0) != 0x80)
    {
      return 2;
    }

    *len = 3;
    *unicode = (c & 0x0F);
    *unicode = (*unicode << 6) | (utf8char[1] & 0x3F);
    *unicode = (*unicode << 6) | (utf8char[2] & 0x3F);
    return 0;
  }

  // 2-byte sequence: 110xxxxx
  if ((c & 0xE0) == 0xC0)
  {
    if (leaveLen < 2 || (utf8char[1] & 0xC0) != 0x80)
    {
      return 2;
    }

    *len = 2;
    *unicode = (c & 0x1F);
    *unicode = (*unicode << 6) | (utf8char[1] & 0x3F);
    return 0;
  }

  // 1-byte sequence: 0xxxxxxx
  if ((c & 0x80) == 0)
  {
    *len = 1;
    *unicode = c;
    return 0;
  }

  // If we reach here, the byte is a continuation byte (10xxxxxx)
  // acting as a leading byte, which is invalid UTF-8.
  return 1;
}