char *my_strcpy(char *dest, char *src)
{
 int i;

 i = 0;
 while (1)
 {
  if (src[i] == '\0')
  {
   dest[i] = '\0';
   return (dest);
  }
  dest[i] = src[i];
  i++;
 }
}