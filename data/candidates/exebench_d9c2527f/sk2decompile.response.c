char *get_word(char *str, int *len) {
  char *p = str;
  int i = 0;
  if (str) {
    while (*p == '-') p++;
    if (*p >= 'a' && *p <= 'z') {
      while (i < 64 && ((p[i] >= '0' && p[i] <= '9') ||
                        (p[i] >= 'a' && p[i] <= 'z') ||
                        (p[i] == '-' || p[i] == '_')))
        i++;
    }
  }
  *len = i;
  return p;
}