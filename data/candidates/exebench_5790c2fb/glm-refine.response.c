char *__cdecl strcpy2(char *s, const char *t)
{
  char *dest = s;

  while ((*dest++ = *t++) != '\0')
    ;

  return s;
}