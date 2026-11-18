char *func0(char *s, char *t) {
  int i, len;
  len = strlen(s);
  for (i = 0; i < len; i++) {
    t[i] = s[i];
  }
  t[len] = '\0';
  return t;
}