void unescape(char *dest, char *src) {
  int i = 0, j;
  for (j = 0; src[j]; j++, i++) {
    if (src[j] == '\\') {
      j++;
      switch (src[j]) {
        case 'a':
          dest[i] = '\a';
          break;
        case 'b':
          dest[i] = '\b';
          break;
        case 'f':
          dest[i] = '\f';
          break;
        case 'n':
          dest[i] = '\n';
          break;
        case 'r':
          dest[i] = '\r';
          break;
        case 't':
          dest[i] = '\t';
          break;
        case 'v':
          dest[i] = '\v';
          break;
        case '\\':
          dest[i] = '\\';
          break;
        case '?':
          dest[i] = '\?';
          break;
        case '\'':
          dest[i] = '\'';
          break;
        case '"':
          dest[i] = '\"';
          break;
        default:
          dest[i] = '\\';
          dest[++i] = src[j];
      }
    } else {
      dest[i] = src[j];
    }
  }
  dest[i] = '\0';
}