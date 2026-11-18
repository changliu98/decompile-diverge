int UnicodeToUtf8(unsigned int unicode, char *utf8) {
  char *p = utf8;
  int len = 0;
  if (unicode < 0x80) {
    *p++ = unicode;
    len = 1;
  } else if (unicode < 0x800) {
    *p++ = (unicode >> 6) | 0xC0;
    *p++ = (unicode & 0x3F) | 0x80;
    len = 2;
  } else if (unicode == 0xFEFF) {
  } else if (unicode >= 0xD800 && unicode <= 0xDFFF) {
  } else if (unicode <= 0xFFFF) {
    *p++ = (unicode >> 12) | 0xE0;
    *p++ = ((unicode >> 6) & 0x3F) | 0x80;
    *p++ = (unicode & 0x3F) | 0x80;
    len = 3;
  }
  *p = '\0';
  return len;
}