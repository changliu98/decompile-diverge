char *_substitute(char *str, char *sub) {
  int i, j;
  char c;
  static char buf[1024];
  j = 0;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ')
      c = sub[0];
    else
      c = str[i];
    buf[j++] = c;
  }
  buf[j] = '\0';
  return buf;
}