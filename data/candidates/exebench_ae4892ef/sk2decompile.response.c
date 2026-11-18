char *my_strcpy(char *dest, const char *src) {
  char *p = dest;
  while (*src) {
    *p = *src;
    p++;
    src++;
  }
  *p = '\0';
  return dest;
}