TU *bit_utf8_to_TU(const char *s, int escape) {
  unsigned char *p;
  unsigned char c;
  size_t len, i = 0;
  TU *tu;
  len = strlen(s);
  if (len >= 65535) {
    bit_utf8_error = 1;
    len = 65535 - 1;
  }
  tu = calloc(2, len + 1);
  if (tu == NULL) {
    bit_utf8_error = 1;
    return NULL;
  }
  while (len > 0 && (c = *s++)) {
    len--;
    if (c < 0x80) {
      if (escape && c == '\\' && len >= 2 &&
          (*s == '"' || *s == '\\' || *s == 'r' || *s == 'n')) {
        c = *s++;
        if (c == 'r')
          tu[i++] = 0x0d;
        else if (c == 'n')
          tu[i++] = 0x0a;
        else
          tu[i++] = c;
      } else
        tu[i++] = c;
    } else if ((c & 0xe0) == 0xc0) {
      if (len > 0) tu[i++] = ((c & 0x1f) << 6) | (s[1] & 0x3f);
      len--;
      s++;
    } else if ((c & 0xf0) == 0xe0) {
      if (len >= 2)
        tu[i++] = ((c & 0x0f) << 12) | ((s[1] & 0x3f) << 6) | (s[2] & 0x3f);
      s += 2;
      len -= 2;
    }
  }
  return tu;
}