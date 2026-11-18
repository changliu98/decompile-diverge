char *ft_strcpy(char *dst, char *src)
{
  do *dst++ = *src++; while(*src);
  return dst;
}