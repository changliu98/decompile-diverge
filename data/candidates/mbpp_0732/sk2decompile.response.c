char *func0(char *s) {
  int i;
  for (i = 0; s[i]; i++) {
    if (s[i] == ' ' || s[i] == ',' || s[i] == '.') s[i] = ':';
  }
  return s;
}