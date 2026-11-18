unsigned utf8BytesToCodePoint(const unsigned char *bytes, unsigned length,
                              unsigned *codePoint) {
  unsigned b0;
  if (length < 1) return 0;
  b0 = bytes[0];
  if ((b0 & 0x80) == 0) {
    *codePoint = b0;
    return 1;
  }
  if ((b0 & 0xe0) == 0xc0) {
    if (length < 2) return 0;
    *codePoint = ((b0 & 0x1f) << 6) | (bytes[1] & 0x3f);
    return 2;
  }
  if ((b0 & 0xf0) == 0xe0) {
    if (length < 3) return 0;
    *codePoint = ((b0 & 0x0f) << 12) | ((bytes[1] & 0x3f) << 6) |
                 (bytes[2] & 0x3f);
    return 3;
  }
  if ((b0 & 0xf8) == 0xf0) {
    if (length < 4) return 0;
    *codePoint = ((b0 & 0x07) << 18) | ((bytes[1] & 0x3f) << 12) |
                 ((bytes[2] & 0x3f) << 6) | (bytes[3] & 0x3f);
    return 4;
  }
  return 0;
}