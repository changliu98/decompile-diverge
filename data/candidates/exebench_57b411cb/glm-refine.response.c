char *__cdecl ft_strcpy(char *dest, const char *src)
{
  char *dest_start = dest;

  while (*src)
  {
    *dest++ = *src++;
  }
  *dest = '\0';

  return dest_start;
}