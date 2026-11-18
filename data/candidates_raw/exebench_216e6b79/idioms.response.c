void str_unescape(char *dest, char *src)
{
  int i; int j = 0;
  for (i = 0; src[i]; i++) {
    if (src[i] == '\\') {
      i++;
      switch (src[i]) {
        case '"':
          dest[j] = '"';
          break;
        case '\'':
          dest[j] = '\'';
          break;
        case '?':
          dest[j] = '?';
          break;
        case '\\':
          dest[j] = '\\';
          break;
        case 'a':
          dest[j] = '\a';
          break;
        case 'b':
          dest[j] = '\b';
          break;
        case 'f':
          dest[j] = '\f';
          break;
        case 'n':
          dest[j] = '\n';
          break;
        case 'r':
          dest[j] = '\r';
          break;
        case 't':
          dest[j] = '\t';
          break;
        case 'v':
          dest[j] = '\v';
          break;
        default:
          dest[j++] = '\\';
          dest[j] = src[i];
          break;
      }
    }
    else {
      dest[j] = src[i];
    }
    j++;
  }
  dest[j] = '\0';
}