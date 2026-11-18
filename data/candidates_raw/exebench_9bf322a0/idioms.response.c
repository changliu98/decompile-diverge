char *strncpy(char *dest, char *src, int n)
{
  int i = -1;
  for ( ; ; )
  {
    ++i;
    int copy = 0;
    if (src[i])
    {
      if (i < n)
        copy = 1;
    }
    if (!copy)
    {
      dest[i] = '\0';
      break;
    }
    else
    {
      dest[i] = src[i];
    }
  }
  return dest;
}