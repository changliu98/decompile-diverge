size_t bytelen_and_check_utf8(const char *str) {
  const unsigned char *p = (const unsigned char *)str;
  const unsigned char *start = p;
  while (*p) {
    unsigned int size = codepoint_size(*p);
    if (size == -1) return -1;
    p++;
    size--;
    while (size) {
      if ((*p & 0xc0) != 0x80) return -1;
      p++;
      size--;
    }
  }
  return p - start;
}