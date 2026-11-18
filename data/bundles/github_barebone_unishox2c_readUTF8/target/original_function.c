int32_t readUTF8(const char *in, int len, int l, int *utf8len) {
  int32_t ret = 0;
  if (l < (len - 1) && (in[l] & 0xE0) == 0xC0 && (in[l + 1] & 0xC0) == 0x80) {
    *utf8len = 2;
    ret = (in[l] & 0x1F);
    ret <<= 6;
    ret += (in[l + 1] & 0x3F);
    if (ret < 0x80)
      ret = 0;
  } else
  if (l < (len - 2) && (in[l] & 0xF0) == 0xE0 && (in[l + 1] & 0xC0) == 0x80
          && (in[l + 2] & 0xC0) == 0x80) {
    *utf8len = 3;
    ret = (in[l] & 0x0F);
    ret <<= 6;
    ret += (in[l + 1] & 0x3F);
    ret <<= 6;
    ret += (in[l + 2] & 0x3F);
    if (ret < 0x0800)
      ret = 0;
  } else
  if (l < (len - 3) && (in[l] & 0xF8) == 0xF0 && (in[l + 1] & 0xC0) == 0x80
          && (in[l + 2] & 0xC0) == 0x80 && (in[l + 3] & 0xC0) == 0x80) {
    *utf8len = 4;
    ret = (in[l] & 0x07);
    ret <<= 6;
    ret += (in[l + 1] & 0x3F);
    ret <<= 6;
    ret += (in[l + 2] & 0x3F);
    ret <<= 6;
    ret += (in[l + 3] & 0x3F);
    if (ret < 0x10000)
      ret = 0;
  }
  return ret;
}