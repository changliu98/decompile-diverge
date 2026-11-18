char *strset(char *s, int c) {
  char *p;
  for (p = s; *p; p++) {
    *p = c;
  }
  return s;
}