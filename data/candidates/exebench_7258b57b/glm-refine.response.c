int __cdecl UnicodeToUtf8(unsigned int src, char *dest)
{
  int len;

  if (src <= 0x7F)
  {
    // 1-byte sequence: 0xxxxxxx
    *dest = (char)src;
    len = 1;
  }
  else if (src <= 0x7FF)
  {
    // 2-byte sequence: 110xxxxx 10xxxxxx
    dest[0] = (char)((src >> 6) | 0xC0);
    dest[1] = (char)((src & 0x3F) | 0x80);
    len = 2;
  }
  else if (src == 0xFEFF || (src >= 0xD800 && src <= 0xDFFF) || src > 0xFFFF)
  {
    // Fallback for invalid or out-of-bounds code points:
    // - BOM (U+FEFF)
    // - Surrogates (U+D800 to U+DFFF)
    // - Code points above the Basic Multilingual Plane (> 0xFFFF)
    // 
    // Note: Preserves original decompiled behavior where none of the branches 
    // are taken, leaving 'dest' unmodified and 'len' uninitialized.
    // (In standard C, reading 'len' here would be undefined behavior)
  }
  else
  {
    // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
    dest[0] = (char)((src >> 12) | 0xE0);
    dest[1] = (char)(((src >> 6) & 0x3F) | 0x80);
    dest[2] = (char)((src & 0x3F) | 0x80);
    len = 3;
  }

  // Null-terminate the destination buffer
  dest[len] = 0;

  return len;
}