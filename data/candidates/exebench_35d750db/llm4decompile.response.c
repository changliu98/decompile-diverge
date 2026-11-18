char *ft_strcpy(char *dst, const char *src)
{
 s2 = src;
 while (*s2 != '\0')
 {
  *dst = *s2;
  s2++;
  dst++;
 }
 *dst = '\0';
 return (dst - (dst - dst));
}