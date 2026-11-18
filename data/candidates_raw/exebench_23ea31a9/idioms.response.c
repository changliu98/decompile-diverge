char *str_escape(char *dst, char *src)
{
  int i = 0; int j = 0;
  int c;
  if (src == ((void *)0))
  {
    dst[0] = '\0';
    return dst;
  }
  while (src[i])
  {
    c = src[i];
    if (c == '%')
    {
      dst[j++] = '_';
      i++;
    }
    else if (c == '\'')
    {
      dst[j] = '\\';
      dst[++j] = src[i++];
      j++;
    }
    else if (c == '\\')
    {
      dst[j] = '\\';
      dst[++j] = src[i++];
      j++;
    }
    else
    {
      dst[j++] = src[i++];
    }
  }
  dst[j] = '\0';
  return dst;
}