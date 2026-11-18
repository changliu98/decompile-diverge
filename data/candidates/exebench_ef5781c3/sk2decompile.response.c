char *strncpy2(char *dest, char *src, int n) {
  char *p = dest;
  while (n-- > 0 && *src != '\0') {
    *p++ = *src++;
  }
  *p = '\0';
  return dest;
}