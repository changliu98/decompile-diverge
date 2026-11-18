char *ft_strcpy(char *dst, char *src)
{
  char *d = dst;
  while (*src)
    *d++ = *src++;
  *d = '\0';
  return (dst);
}