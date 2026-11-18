ssize_t bytelen_and_check_utf8(uint8_t *str)

{
  size_t size;
  uint8_t *p;
  uint8_t *str_local;
  
  p = str;
  while( true ) {
    if (*p == '\0') {
      return (long)p - (long)str;
    }
    size = codepoint_size(*p);
    if (size == 0xffffffffffffffff) break;
    while( true ) {
      p = p + 1;
      size = size - 1;
      if (size == 0) break;
      if ((*p & 0xc0) != 0x80) {
        return -1;
      }
    }
  }
  return -1;
}