char *mystrncpy(char *dest, char *src, int n) {
  int i;
  char *p = dest;
  for (i = 0; i < n && *src != '\0'; i++) {
    *p++ = *src++;
  }
  *p = '\0';
  return dest;
}