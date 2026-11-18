int str_linecount(char *str, int maxlen, int *curlen) {
  int lines = 1;
  while (*str) {
    if (*str == '\n') {
      lines++;
      *curlen = 0;
    } else {
      (*curlen)++;
      if (*curlen >= maxlen) {
        lines++;
        *curlen = 0;
      }
    }
    str++;
  }
  return lines;
}