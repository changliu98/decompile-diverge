char *envstring(char *s) {
  char *p;
  for (p = s; *p; p++) {
    if (*p == '-')
      *p = '_';
    else if (*p >= 'a' && *p <= 'z')
      *p -= 'a' - 'A';
    else if (*p < 'A' || *p > 'Z') {
      *s = '\0';
      return s;
    }
  }
  return s;
}