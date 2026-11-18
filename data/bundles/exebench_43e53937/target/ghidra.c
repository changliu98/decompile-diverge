void Utf32toUtf8(uint codepoint,char *utf8Buf)

{
  byte bVar1;
  char *utf8Buf_local;
  uint codepoint_local;
  
  bVar1 = (byte)codepoint;
  if (codepoint < 0x80) {
    *utf8Buf = bVar1;
    utf8Buf[1] = '\0';
  }
  else if (codepoint < 0x800) {
    *utf8Buf = (byte)(codepoint >> 6) | 0xc0;
    utf8Buf[1] = bVar1 & 0x3f | 0x80;
    utf8Buf[2] = '\0';
  }
  else if (codepoint < 0x10000) {
    *utf8Buf = (byte)(codepoint >> 0xc) | 0xe0;
    utf8Buf[1] = (byte)(codepoint >> 6) & 0x3f | 0x80;
    utf8Buf[2] = bVar1 & 0x3f | 0x80;
    utf8Buf[3] = '\0';
  }
  else if (codepoint < 0x200000) {
    *utf8Buf = (byte)(codepoint >> 0x12) | 0xf0;
    utf8Buf[1] = (byte)(codepoint >> 0xc) & 0x3f | 0x80;
    utf8Buf[2] = (byte)(codepoint >> 6) & 0x3f | 0x80;
    utf8Buf[3] = bVar1 & 0x3f | 0x80;
    utf8Buf[4] = '\0';
  }
  else {
    *utf8Buf = '?';
    utf8Buf[1] = '\0';
  }
  return;
}