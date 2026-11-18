void __cdecl escape(char *s, const char *t)
{
  size_t j = 0;
  
  for (size_t i = 0; t[i] != '\0'; ++i)
  {
    switch (t[i])
    {
      case '\a':  // 7
        s[j++] = '\\';
        s[j] = 'a';
        break;
      case '\b':  // 8
        s[j++] = '\\';
        s[j] = 'b';
        break;
      case '\t':  // 9
        s[j++] = '\\';
        s[j] = 't';
        break;
      case '\n':  // 10
        s[j++] = '\\';
        s[j] = 'n';
        break;
      case '\v':  // 11
        s[j++] = '\\';
        s[j] = 'v';
        break;
      case '\f':  // 12
        s[j++] = '\\';
        s[j] = 'f';
        break;
      case '\r':  // 13
        s[j++] = '\\';
        s[j] = 'r';
        break;
      case '\"':  // 34
        s[j++] = '\\';
        s[j] = '\"';
        break;
      case '\'':  // 39
        s[j++] = '\\';
        s[j] = '\'';
        break;
      case '\?':  // 63
        s[j++] = '\\';
        s[j] = '\?';
        break;
      case '\\':  // 92
        s[j++] = '\\';
        s[j] = '\\';
        break;
      default:
        s[j] = t[i];
        break;
    }
    ++j;
  }
  
  s[j] = '\0';
}