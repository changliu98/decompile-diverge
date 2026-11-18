char *ft_strcpy(char *s1, const char *s2)
{
 char *tmp;

 tmp = s1;
 while (*s2 != '\0')
  *tmp++ = *s2++;
 *tmp = '\0';
 return (s1);
}