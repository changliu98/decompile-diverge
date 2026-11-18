char *my_strncpy(char *dest, char *src, int n)
{
  int i;
  char test;

  i = 0;
  while (1)
    {
      test = ((i < n) && (src[i] != '\0')) ? 1 : 0;
      if (test)
 {
   dest[i] = src[i];
   i++;
 }
      else
 {
   if (i < n)
     dest[i] = '\0';
   break;
 }
    }
  return (dest);
}