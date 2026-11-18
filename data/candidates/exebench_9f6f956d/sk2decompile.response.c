int ckstrncpy(char *dst, const char *src, int maxlen) {
  int i;
  if (maxlen < 1 || src == NULL || dst == NULL) {
    if (dst != NULL) {
      *dst = '\0';
    }
    return 0;
  }
  for (i = 0; src[i] != '\0' && i < maxlen - 1; i++) {
    dst[i] = src[i];
  }
  dst[i] = '\0';
  return i;
}