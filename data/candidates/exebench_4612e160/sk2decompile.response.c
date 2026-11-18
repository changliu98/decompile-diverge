unsigned int utf8_decode_v2(const unsigned char *str, unsigned int len,
                            unsigned int *bytes) {
  if (len < 1 || str[0] == 0) {
    if (bytes) *bytes = 0;
    return 0xffffffff;
  }
  if ((str[0] & 0x80) == 0) {
    if (bytes) *bytes = 1;
    return str[0] & 0x7f;
  }
  if ((str[0] & 0xe0) == 0xc0) {
    if (bytes) *bytes = 2;
    if (len < 2 || str[1] == 0) return 0xffffffff;
    return ((str[0] & 0x1f) << 6) | (str[1] & 0x3f);
  }
  if ((str[0] & 0xf0) == 0xe0) {
    if (bytes) *bytes = 3;
    if (len < 3 || str[1] == 0 || str[2] == 0) return 0xffffffff;
    return ((str[0] & 0x0f) << 12) | ((str[1] & 0x3f) << 6) | (str[2] & 0x3f);
  }
  if ((str[0] & 0xf8) == 0xf0) {
    if (bytes) *bytes = 4;
    if (len < 4 || str[1] == 0 || str[2] == 0 || str[3] == 0) return 0xffffffff;
    return ((str[0] & 0x07) << 15) | ((str[1] & 0x3f) << 12) |
           ((str[2] & 0x3f) << 6) | (str[3] & 0x3f);
  }
  if (bytes) *bytes = 0;
  return 0xffffffff;
}