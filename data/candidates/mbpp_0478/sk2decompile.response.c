char *func0(char *s) {
  int j = 0;
  int i;
  for (i = 0; s[i]; i++) {
    if (!isalpha(s[i])) {
      buf[j++] = s[i];
    }
  }
  buf[j] = 0;
  return buf;
}