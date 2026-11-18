char *strcpy_x86_64_fast(char *dest, const char *src) {
  char *ret = dest;
  char c;
  do {
    c = *src++;
    *dest++ = c;
  } while (c);
  return ret;
}