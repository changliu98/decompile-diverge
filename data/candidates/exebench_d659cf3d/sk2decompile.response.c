int tt_unesc(char *str, char esc) {
  char *p;
  int n = 0;
  while (*str != esc) {
    if (*str == '\0') return 0;
    str++;
  }
  p = str;
  while (*str) {
    if (*str == esc) {
      str++;
      n++;
    }
    *p = *str;
    p++;
    str++;
  }
  return n;
}