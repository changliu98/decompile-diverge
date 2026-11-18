char *ft_strcpy(char *dst, const char *src) {
  char *d;
  char c;
  d = dst;
  while ((c = *src++)) *d++ = c;
  return (dst);
}