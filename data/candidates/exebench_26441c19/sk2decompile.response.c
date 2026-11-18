int Utf8ToUnicode(unsigned char *utf8, unsigned int *unicode, int *utf8len,
                  int len) {
  unsigned char c = utf8[0];
  if ((c & 0xf8) == 0xf0) {
    if (len < 4 || (utf8[1] & 0xc0) != 0x80 || (utf8[2] & 0xc0) != 0x80 ||
        (utf8[3] & 0xc0) != 0x80)
      return 2;
    *utf8len = 4;
    *unicode |= c & 0x07;
    *unicode <<= 6;
    *unicode |= utf8[1] & 0x3f;
    *unicode <<= 6;
    *unicode |= utf8[2] & 0x3f;
    *unicode <<= 6;
    *unicode |= utf8[3] & 0x3f;
  } else if ((c & 0xf0) == 0xe0) {
    if (len < 3 || (utf8[1] & 0xc0) != 0x80 || (utf8[2] & 0xc0) != 0x80)
      return 2;
    *utf8len = 3;
    *unicode |= c & 0x0f;
    *unicode <<= 6;
    *unicode |= utf8[1] & 0x3f;
    *unicode <<= 6;
    *unicode |= utf8[2] & 0x3f;
  } else if ((c & 0xe0) == 0xc0) {
    if (len < 2 || (utf8[1] & 0xc0) != 0x80) return 2;
    *utf8len = 2;
    *unicode |= c & 0x1f;
    *unicode <<= 6;
    *unicode |= utf8[1] & 0x3f;
  } else if ((c & 0x80) == 0x00) {
    *utf8len = 1;
    *unicode = c;
  } else
    return 1;
  return 0;
}