
char *my_strcpy(char *dest, char *src)
{
  int lp;

  lp = 0;
  while (src[lp] != '\0')
    {
      dest[lp] = src[lp];
      ++lp;
    }
  dest[lp] = '\0';
  return (dest);
}
