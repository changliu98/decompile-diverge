void lemon_strcpy(char *dst, const char *src) {
  char c;
  do {
    c = *src++;
    *dst++ = c;
  } while (c != '\0');
}