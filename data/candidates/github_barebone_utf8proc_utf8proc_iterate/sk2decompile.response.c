utf8proc_ssize_t utf8proc_iterate(const unsigned char *str, utf8proc_ssize_t len,
                                  ucs4_t *ppt) {
  const unsigned char *end, *s;
  ucs4_t c;
  *ppt = -1;
  if (len == 0) return 0;
  end = str + (len < 0 ? 4 : len);
  s = str;
  c = *s++;
  if (c < 0x80) {
    *ppt = c;
    return 1;
  } else if (c < 0xc2 || c > 0xdf)
    return -3;
  else if (c < 0xe0) {
    if (s >= end || (s[0] & 0xc0) != 0x80) return -3;
    *ppt = ((c & 0x1f) << 6) | (s[0] & 0x3f);
    return 2;
  } else if (c < 0xf0) {
    if (s + 1 >= end || (s[0] & 0xc0) != 0x80 || (s[1] & 0xc0) != 0x80)
      return -3;
    if (c == 0xed && s[0] >= 0xa0) return -3;
    c = ((c & 0x0f) << 12) | ((s[0] & 0x3f) << 6) | (s[1] & 0x3f);
    if (c < 0x800) return -3;
    *ppt = c;
    return 3;
  } else {
    if (s + 2 >= end || (s[0] & 0xc0) != 0x80 || (s[1] & 0xc0) != 0x80 ||
        (s[2] & 0xc0) != 0x80)
      return -3;
    if (c == 0xf0 && s[0] < 0x90) return -3;
    if (c == 0xf4 && s[0] > 0x8f) return -3;
    *ppt = ((c & 0x07) << 18) | ((s[0] & 0x3f) << 12) | ((s[1] & 0x3f) << 6) |
           (s[2] & 0x3f);
    return 4;
  }
}