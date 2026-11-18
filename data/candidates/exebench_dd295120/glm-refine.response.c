char *__cdecl ft_strcpy(char *s1, const char *s2)
{
  char *s1a = s1;

  while (*s2)
    *s1a++ = *s2++;
  *s1a = 0;

  return s1;
}