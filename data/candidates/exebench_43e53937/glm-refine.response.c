void __cdecl Utf32toUtf8(unsigned int codepoint, char *utf8Buf)
{
  if (codepoint < 0x80)
  {
    // 1-byte sequence: 0xxxxxxx
    utf8Buf[0] = codepoint;
    utf8Buf[1] = 0;
  }
  else if (codepoint < 0x800)
  {
    // 2-byte sequence: 110xxxxx 10xxxxxx
    utf8Buf[0] = (codepoint >> 6) | 0xC0;
    utf8Buf[1] = (codepoint & 0x3F) | 0x80;
    utf8Buf[2] = 0;
  }
  else if (codepoint < 0x10000)
  {
    // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
    utf8Buf[0] = (codepoint >> 12) | 0xE0;
    utf8Buf[1] = ((codepoint >> 6) & 0x3F) | 0x80;
    utf8Buf[2] = (codepoint & 0x3F) | 0x80;
    utf8Buf[3] = 0;
  }
  else if (codepoint < 0x200000)
  {
    // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    utf8Buf[0] = (codepoint >> 18) | 0xF0;
    utf8Buf[1] = ((codepoint >> 12) & 0x3F) | 0x80;
    utf8Buf[2] = ((codepoint >> 6) & 0x3F) | 0x80;
    utf8Buf[3] = (codepoint & 0x3F) | 0x80;
    utf8Buf[4] = 0;
  }
  else
  {
    // Codepoint out of range, write '?' as a fallback
    utf8Buf[0] = 63; // '?'
    utf8Buf[1] = 0;
  }
}