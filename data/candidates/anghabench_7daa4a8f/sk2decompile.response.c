static char *stb_skipnewline(char *s) {
  if (*s == '\r' || *s == '\n') {
    if (*s + s[1] == '\r' + '\n') ++s;
    ++s;
  }
  return s;
}