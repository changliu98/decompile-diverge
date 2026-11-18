void escape(char *dest, char *src)
{
  int i; int j = 0;
  int c;
  for (i = 0; src[i]; i++)
  {
    c = src[i];
    switch (c)
    {
      case '\t':
        dest[j++] = '\\';
        dest[j++] = 't';
        break;
      case '\n':
        dest[j++] = '\\';
        dest[j++] = 'n';
        break;
      case '\"':
        dest[j++] = '\\';
        dest[j++] = '\"';
        break;
      case '\\':
        dest[j++] = '\\';
        dest[j++] = '\\';
        break;
      default:
        dest[j++] = c;
    }
  }
  dest[j++] = src[i];
}