char *__cdecl ft_strcpy(char *dst, const char *src)
{
  char *original_dst = dst;

  do
  {
    *dst = *src;
    dst++;
    src++;
  }
  while (*dst != '\0');

  return original_dst;
}