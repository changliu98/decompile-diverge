char *strcpyend(char *dst, const char *src) {
  char c;
  do {
    c = *src++;
    *dst++ = c;
  } while (c != '\0');
  return dst - 1;
}