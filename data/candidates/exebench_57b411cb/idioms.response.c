char *ft_strcpy(char *dest, char *src)
{
 char *d = dest;
 while(*src)
  *d++ = *src++;
 *d = '\0';
 return dest;
}