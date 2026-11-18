char *ft_strcpy(char *dest, const char *src)
{
 char *tmp;

 tmp = dest;
 while (*src)
  *(dest++) = *(src++);
 *dest = '\0';
 return (tmp);
}