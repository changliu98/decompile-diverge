char *ft_strcpy(char *dest, char *src)
{
 long i;

 i = 0;
 while (1)
 {
  dest[i] = src[i];
  if ((int)src[i++] == '\0')
   return (dest);
 }
}