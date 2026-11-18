int cpy(char *dest, char *src)
{
  int i;

  i = 0;
  while (1)
    {
      if ((char)(src[i] == '\0' || i > 100) == 0)
 {
   dest[i] = src[i];
   i++;
 }
      else
 {
   dest[i] = '\0';
   return (0);
 }
    }
}