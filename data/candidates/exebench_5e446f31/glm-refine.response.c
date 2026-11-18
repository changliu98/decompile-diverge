char *__cdecl copy2(char *s1, const char *s2)
{
  char *dest = s1;

  while ((*dest++ = *s2++) != '\0')
    ;

  return s1;
}