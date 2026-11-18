void charset_remove(char *str, char c) {
  char *p, *q;
  p = q = str;
  while (*p) {
    if (*p != c) *q++ = *p;
    p++;
  }
  *q = '\0';
}