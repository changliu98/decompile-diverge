void escape(char s[], char t[]) {
  int i, j;
  int c;
  for (i = 0, j = 0; t[i] != '\0'; i++) {
    c = t[i];
    switch (c) {
      case '\t':
        s[j++] = '\\';
        s[j++] = 't';
        break;
      case '\n':
        s[j++] = '\\';
        s[j++] = 'n';
        break;
      case ' ':
        s[j++] = '\\';
        s[j++] = 'b';
        break;
      default:
        s[j++] = t[i];
        break;
    }
  }
  s[j] = '\0';
}