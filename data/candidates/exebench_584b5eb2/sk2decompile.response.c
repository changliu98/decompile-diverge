char *substitute(char *str, char old, char new) {
  char *p;
  p = str;
  if (str != NULL) {
    while (*p != '\0') {
      if (*p == old) {
        *p = new;
        return str;
      }
      p++;
    }
  }
  return str;
}