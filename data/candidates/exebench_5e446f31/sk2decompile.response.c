void copy2(char *s, char *t) {
  char c;
  while (1) {
    c = *t;
    *s = c;
    if (c == '\0') break;
    s++;
    t++;
  }
}