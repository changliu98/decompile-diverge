
char *ft_strcpy(char *dst, const char *src)
{
 char *d;

 d = dst;
 while ((*d++ = *src++))
  ;
 return (dst);
}
