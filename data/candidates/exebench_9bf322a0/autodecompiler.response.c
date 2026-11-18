char *my_strncpy(char *dest, char *src, int n)
{
  int i;

  i = -1;
  while (((((src[++i]) ? 1 : ((i < n) ? 1 : 0)) ? 1 : 0))
 {
   dest[i] = src[i];
 }
  dest[i] = '\0';
  return (dest);
}