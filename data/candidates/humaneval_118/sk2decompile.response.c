char *func0(char *s) {
  static char buf[1];
  int i;
  for (i = strlen(s) - 2; i >= 1; i--) {
    if (strchr("AEIOUaeiou", s[i]) && !strchr("AEIOUaeiou", s[i + 1]) &&
        !strchr("AEIOUaeiou", s[i - 1])) {
      buf[0] = s[i];
      return buf;
    }
  }
  buf[0] = '\0';
  return buf;
}