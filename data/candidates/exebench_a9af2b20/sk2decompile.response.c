char *stpCpy(char *dst, const char *src) {
  char c;
  do {
    c = *src++;
    *dst = c;
    if (c != '\0') dst++;
  } while (c != '\0');
  return dst;
}