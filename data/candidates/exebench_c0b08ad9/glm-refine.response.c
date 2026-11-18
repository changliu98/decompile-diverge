void __cdecl escape(char *s, char *t)
{
  int i = 0;
  
  for (int j = 0; t[j] != '\0'; ++j)
  {
    if (s[i] == '\0')
      break;

    if (t[j] == '\t')
    {
      s[i++] = '\\';
      s[i++] = 't';
    }
    else if (t[j] == '\n')
    {
      s[i++] = '\\';
      s[i++] = 'n';
    }
    else
    {
      s[i++] = t[j];
    }
  }
}