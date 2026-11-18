int str_copy(char *dst, char *src) {
  int i = 0;
  for (;;) {
    *dst = *src;
    if (*dst == '\0') return i;
    dst++;
    src++;
    i++;
    *dst = *src;
    if (*dst == '\0') return i;
    dst++;
    src++;
    i++;
    *dst = *src;
    if (*dst == '\0') return i;
    dst++;
    src++;
    i++;
    *dst = *src;
    if (*dst == '\0') return i;
    dst++;
    src++;
    i++;
  }
}