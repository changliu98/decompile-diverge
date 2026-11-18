char *__cdecl ft_strcpy(char *dst, const char *src)
{
  int i = -1;

  // Pre-increment i to start at 0. Loop until the null terminator is copied.
  while (dst[i] = src[++i])
    ;

  return dst;
}