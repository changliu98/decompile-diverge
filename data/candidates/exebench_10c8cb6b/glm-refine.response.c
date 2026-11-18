char *__cdecl stringCopy(char *s, const char *t)
{
  while ((*s++ = *t++) != '\0')
    ;

  return --s;
}