char *my_strncpy(char *dest, char *src, int n)
{
  int lp;

  lp = -1;
  while (src[++lp] != '\0' && lp < n)
    dest[lp] = src[lp];
  dest[lp] = '\0';
  return (dest);
}