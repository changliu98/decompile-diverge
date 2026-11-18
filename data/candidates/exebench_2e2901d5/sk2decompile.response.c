void str_copy(char *dest, const char *src) {
  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
}