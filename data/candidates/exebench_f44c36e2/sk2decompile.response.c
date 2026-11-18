void strcpymax(char *dst, const char *src, int maxlen) {
  int i;
  if (maxlen == 0) {
    *dst = '\0';
    return;
  }
  for (i = 0; *src && i < maxlen - 1; i++) {
    *dst++ = *src++;
  }
  *dst = '\0';
}