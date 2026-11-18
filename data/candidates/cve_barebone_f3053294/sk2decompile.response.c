char *utf_16le_to_utf_8_truncated(const unsigned short *utf_16le, char *utf_8,
                                  unsigned int max_bytes) {
  unsigned int c;
  unsigned short c1, c2;
  char *p = utf_8;
  unsigned int bytes_left = max_bytes;
  if (bytes_left == 0) return utf_8;
  while ((c1 = *utf_16le++) != 0) {
    if (c1 >= 0xd800 && c1 < 0xdc00) {
      c2 = *utf_16le;
      if (c2 == 0)
        c = 0xfffd;
      else if (c2 >= 0xdc00 && c2 < 0xe000)
        c = ((c1 - 0xd800) << 10) | (c2 - 0xdc00) + 0x10000;
      else
        c = 0xfffd;
    } else if (c1 >= 0xdc00 && c1 < 0xe000)
      c = 0xfffd;
    else
      c = c1;
    if (c < 0x80) {
      if (bytes_left < 2) break;
      *p++ = c;
      bytes_left--;
    } else if (c < 0x800) {
      if (bytes_left < 3) break;
      *p++ = (c >> 6) | 0xc0;
      *p++ = (c & 0x3f) | 0x80;
      bytes_left -= 2;
    } else if (c < 0x10000) {
      if (bytes_left < 4) break;
      *p++ = (c >> 12) | 0xe0;
      *p++ = ((c >> 6) & 0x3f) | 0x80;
      *p++ = (c & 0x3f) | 0x80;
      bytes_left -= 3;
    } else {
      if (bytes_left < 5) break;
      *p++ = (c >> 18) | 0xf0;
      *p++ = ((c >> 12) & 0x3f) | 0x80;
      *p++ = ((c >> 6) & 0x3f) | 0x80;
      *p++ = (c & 0x3f) | 0x80;
      bytes_left -= 4;
    }
  }
  *p = '\0';
  return p;
}