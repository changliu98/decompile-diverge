char *strcpy(char *dest, const char *src) {
  char *ret = dest;
  char c;
  do {
    c = *src++;
    *dest++ = c;
  } while (c != '\0');
  return ret;
}