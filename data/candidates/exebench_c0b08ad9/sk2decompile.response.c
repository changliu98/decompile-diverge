void escape(char s[], char t[]) {
  int i, j;
  int c;
  for (i = 0, j = 0; s[i] != '\0' && t[j] != '\0'; j++) {
    c = t[j];
    if (c == '\t') {
      s[i++] = '\\';
      s[i++] = 't';
    } else if (c == '\n') {
      s[i++] = '\\';
      s[i++] = 'n';
    } else {
      s[i++] = t[j];
    }
  }
}