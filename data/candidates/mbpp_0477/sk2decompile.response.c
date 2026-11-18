void _strlwr(const char *src, char *dst) {
  int i;
  for (i = 0; src[i]; i++) {
    dst[i] = tolower((unsigned char)src[i]);
  }
  dst[i] = '\0';
}