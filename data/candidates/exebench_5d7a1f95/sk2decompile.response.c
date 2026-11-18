void escape(char s[], char t[]) {
  int i, j;
  i = 0;
  for (j = 0; t[j] != '\0'; j++) {
    switch (t[j]) {
      case '\a':
        s[i] = '\\';
        i++;
        s[i] = 'a';
        break;
      case '\b':
        s[i] = '\\';
        i++;
        s[i] = 'b';
        break;
      case '\t':
        s[i] = '\\';
        i++;
        s[i] = 't';
        break;
      case '\n':
        s[i] = '\\';
        i++;
        s[i] = 'n';
        break;
      case '\v':
        s[i] = '\\';
        i++;
        s[i] = 'v';
        break;
      case '\f':
        s[i] = '\\';
        i++;
        s[i] = 'f';
        break;
      case '\r':
        s[i] = '\\';
        i++;
        s[i] = 'r';
        break;
      case '\"':
        s[i] = '\\';
        i++;
        s[i] = '\"';
        break;
      case '\'':
        s[i] = '\\';
        i++;
        s[i] = '\'';
        break;
      case '\?':
        s[i] = '\\';
        i++;
        s[i] = '\?';
        break;
      case '\\':
        s[i] = '\\';
        i++;
        s[i] = '\\';
        break;
      default:
        s[i] = t[j];
        break;
    }
    i++;
  }
  s[i] = '\0';
}