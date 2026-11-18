
char *my_strncpy(char *dest, char *src, int n)
{
  int lp;

  lp = 0;
  while (lp < n && src[lp] != '\0')
    {
      dest[lp] = src[lp];
      ++lp;
    }
  if (lp < n)
    dest[lp] = '\0';
  return (dest);
}
