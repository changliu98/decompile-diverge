char *mystpcpy(char *dest, const char *src) {
  char c;
  while (1) {
    c = *src;
    *dest = c;
    if (c == '\0') {
      return dest;
    }
    src++;
    dest++;
  }
}