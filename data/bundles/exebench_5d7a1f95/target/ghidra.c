void escape(char *s,char *t)

{
  int j;
  int i;
  char *t_local;
  char *s_local;
  
  j = 0;
  for (i = 0; t[i] != '\0'; i = i + 1) {
    switch(t[i]) {
    case '\a':
      s[j] = '\\';
      j = j + 1;
      s[j] = 'a';
      break;
    case '\b':
      s[j] = '\\';
      j = j + 1;
      s[j] = 'b';
      break;
    case '\t':
      s[j] = '\\';
      j = j + 1;
      s[j] = 't';
      break;
    case '\n':
      s[j] = '\\';
      j = j + 1;
      s[j] = 'n';
      break;
    case '\v':
      s[j] = '\\';
      j = j + 1;
      s[j] = 'v';
      break;
    case '\f':
      s[j] = '\\';
      j = j + 1;
      s[j] = 'f';
      break;
    case '\r':
      s[j] = '\\';
      j = j + 1;
      s[j] = 'r';
      break;
    default:
      s[j] = t[i];
      break;
    case '\"':
      s[j] = '\\';
      j = j + 1;
      s[j] = '\"';
      break;
    case '\'':
      s[j] = '\\';
      j = j + 1;
      s[j] = '\'';
      break;
    case '?':
      s[j] = '\\';
      j = j + 1;
      s[j] = '?';
      break;
    case '\\':
      s[j] = '\\';
      j = j + 1;
      s[j] = '\\';
    }
    j = j + 1;
  }
  s[j] = '\0';
  return;
}