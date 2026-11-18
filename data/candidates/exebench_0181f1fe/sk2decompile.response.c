int ellipsis(char *str, int len) {
  int multibyte = 0;
  char *p = str;
  int n;
  if (len < 0 || str == NULL) return 0;
  if (len < 3) {
    str[len] = '\0';
    return 1;
  }
  n = len - 3;
  while (*p && n) {
    if (multibyte)
      multibyte = 0;
    else if (*p & 0x80)
      multibyte = 1;
    p++;
    n--;
  }
  n = 3;
  while (*p++ && --n)
    ;
  if (*p && !n) {
    str[len] = '\0';
    *--p = '.';
    *--p = '.';
    if (!multibyte && *--p & 0x80) *p = '.';
  }
  return 1;
}