static ssize_t bytelen_and_check_utf8(const uint8_t *str) {
  const uint8_t *p = str;
  while (*p != '\0') {
    size_t size = codepoint_size(*p);
    if (size == SIZE_MAX) return -1;
    p++; size--;
    while (size > 0) {
      // Check that any middle bytes are of the form 0x10xx xxxx
      if ((*p & 0xc0) != 0x80)
        return -1;
      p++; size--;
    }
  }

#ifdef DEBUG
  size_t num = p - str;
  assert(num == strlen((char *)str));
#endif

  return p - str;
}