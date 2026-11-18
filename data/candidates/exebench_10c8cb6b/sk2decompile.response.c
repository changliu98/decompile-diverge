char *stringCopy(char *dest, const char *src) {
  char c;
  while ((c = *src) != '\0') {
    *dest++ = c;
    src++;
  }
  return dest;
}