char *mystrncpy(char *dest, char *src, int n)
{
  char *tmp;
  int i;

  tmp = dest;
  i = 0;
  while (1)
    {
      if (((i < n) && (*tmp = *src++)) || (i >= n))
 {
   *dest++ = '\0';
   return (tmp);
 }
      i++;
    }
}