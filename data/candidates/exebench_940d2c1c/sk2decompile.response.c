void escape(char s[], char t[]) {
  int i, j;
  int c;
  for (i = 0, j = 0; t[j] != '\0'; i++, j++) {
    c = t[j];
    switch (c) {
      case '\n':
        s[i++] = '\\';
        s[i] = 'n';
        break;
      case '\t':
        s[i++] = '\\';
        s[i] = 't';
        break;
      case '\\':
        s[i++] = '\\';
        s[i] = '\\';
        break;
      case '\"':
        s[i++] = '\\';
        s[i] = '\"';
        break;
      default:
        s[i] = t[j];
        break;
    }
  }
  s[i] = t[j];
}