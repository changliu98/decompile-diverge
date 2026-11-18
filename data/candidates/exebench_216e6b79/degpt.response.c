void unescape(char *s,char *t)

{
  int j;
  int i;
  char *t_local;
  char *s_local;
  
  j = 0;
  for (i = 0; t[i] != '\0'; i = i + 1) {
    if (t[i] == '\\') {
      i = i + 1;
      switch(t[i]) {
      case '\"':
        s[j] = '\"';
        break;
      default:
        s[j] = '\\';
        j = j + 1;
        s[j] = t[i];
        break;
      case '\'':
        s[j] = '\'';
        break;
      case '?':
        s[j] = '?';
        break;
      case '\\':
        s[j] = '\\';
        break;
      case 'a':
        s[j] = '\a';
        break;
      case 'b':
        s[j] = '\b';
        break;
      case 'f':
        s[j] = '\f';
        break;
      case 'n':
        s[j] = '\n';
        break;
      case 'r':
        s[j] = '\r';
        break;
      case 't':
        s[j] = '\t';
        break;
      case 'v':
        s[j] = '\v';
      }
    }
    else {
      s[j] = t[i];
    }
    j = j + 1;
  }
  s[j] = '\0';
  return;
}