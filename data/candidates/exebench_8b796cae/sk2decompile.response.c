int unicode_to_utf8(char *buf, unsigned int unicode) {
  char *p = buf;
  if (unicode < 0x80) {
    *p++ = unicode;
  } else if (unicode < 0x800) {
    *p++ = 0xc0 | (unicode >> 6);
    *p++ = 0x80 | (unicode & 0x3f);
  } else if (unicode < 0x10000) {
    *p++ = 0xe0 | (unicode >> 12);
    *p++ = 0x80 | ((unicode >> 6) & 0x3f);
    *p++ = 0x80 | (unicode & 0x3f);
  } else if (unicode < 0x200000) {
    *p++ = 0xf0 | (unicode >> 18);
    *p++ = 0x80 | ((unicode >> 12) & 0x3f);
    *p++ = 0x80 | ((unicode >> 6) & 0x3f);
    *p++ = 0x80 | (unicode & 0x3f);
  } else {
    *p++ = 0xf8 | (unicode >> 24);
    *p++ = 0x80 | ((unicode >> 18) & 0x3f);
    *p++ = 0x80 | ((unicode >> 12) & 0x3f);
    *p++ = 0x80 | ((unicode >> 6) & 0x3f);
    *p++ = 0x80 | (unicode & 0x3f);
  }
  *p = '\0';
  return p - buf;
}