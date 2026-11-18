char *my_strcpy(char *dest, char *src)
{
  int lp;

  lp = -1;
  while (src[++lp] != '\0')
    dest[lp] = src[lp];
  dest[lp] = '\0';
  return (dest);
}