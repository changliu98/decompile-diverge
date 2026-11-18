char *strichr(char *s, int c) {
  char *p;
  if (s) {
    for (p = s; *p; p++)
      ;
    for (; p >= s; p--) *(p + 1) = *p;
    *s = c;
  }
  return s;
}