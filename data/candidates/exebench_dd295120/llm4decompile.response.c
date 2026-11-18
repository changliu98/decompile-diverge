char *ft_strcpy(char *dest, const char *src)
{
 keep = dest;
 while (*src)
  *dest++ = *src++;
 *dest = '\0';
 return (keep);
}