char *str_cpy(char *dest, const char *src) {
  char *d = dest;
  char c;
  do {
    c = *src++;
    *d++ = c;
  } while (c != '\0');
  return dest;
}