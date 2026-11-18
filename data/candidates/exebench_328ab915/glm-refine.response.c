int __cdecl runetochar(char *s, int c)
{
  int ca = c;

  // Clamp out-of-range code points to the Unicode replacement character (U+FFFD)
  if (c > 0x10FFFF) {
    ca = 0xFFFD;
  }

  if (ca < 0x80) {
    // 1-byte sequence: 0xxxxxxx
    *s = (char)ca;
    return 1;
  } 
  else if (ca < 0x800) {
    // 2-byte sequence: 110xxxxx 10xxxxxx
    *s     = (char)((ca >> 6) | 0xC0);
    s[1]   = (char)((ca & 0x3F) | 0x80);
    return 2;
  } 
  else if (ca < 0x10000) {
    // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
    *s     = (char)((ca >> 12) | 0xE0);
    s[1]   = (char)(((ca >> 6) & 0x3F) | 0x80);
    s[2]   = (char)((ca & 0x3F) | 0x80);
    return 3;
  } 
  else {
    // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    *s     = (char)((ca >> 18) | 0xF0);
    s[1]   = (char)(((ca >> 12) & 0x3F) | 0x80);
    s[2]   = (char)(((ca >> 6) & 0x3F) | 0x80);
    s[3]   = (char)((ca & 0x3F) | 0x80);
    return 4;
  }
}