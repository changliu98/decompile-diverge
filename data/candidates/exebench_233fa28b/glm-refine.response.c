size_t __cdecl utf8BytesToCodePoint(const char *buf, size_t len, int *cp)
{
  unsigned __int8 byte;

  if (len == 0)
    return 0;

  byte = (unsigned __int8)*buf;

  // Check if it's an ASCII character (0xxxxxxx)
  if ((byte & 0x80) == 0)
  {
    *cp = byte;
    return 1;
  }

  // Check for 2-byte sequence (110xxxxx)
  if ((byte & 0xE0) == 0xC0)
  {
    if (len >= 2)
    {
      *cp = ((byte & 0x1F) << 6) | (buf[1] & 0x3F);
      return 2;
    }
    return 0;
  }

  // Check for 3-byte sequence (1110xxxx)
  if ((byte & 0xF0) == 0xE0)
  {
    if (len >= 3)
    {
      *cp = ((byte & 0x0F) << 12) | ((buf[1] & 0x3F) << 6) | (buf[2] & 0x3F);
      return 3;
    }
    return 0;
  }

  // Check for 4-byte sequence (11110xxx)
  if ((byte & 0xF8) == 0xF0)
  {
    if (len >= 4)
    {
      *cp = ((byte & 0x07) << 18) | ((buf[1] & 0x3F) << 12) | ((buf[2] & 0x3F) << 6) | (buf[3] & 0x3F);
      return 4;
    }
  }

  // Invalid byte or truncated sequence
  return 0;
}