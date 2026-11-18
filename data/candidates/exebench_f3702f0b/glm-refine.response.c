void __cdecl escape(char *s, char *t)
{
  int j = 0;

  for (int i = 0; t[i]; ++i)
  {
    switch (t[i])
    {
      case '\t': // 9
        s[j++] = '\\';
        s[j++] = 't';
        break;
      case '\n': // 10
        s[j++] = '\\';
        s[j++] = 'n';
        break;
      case ' ':  // 32
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