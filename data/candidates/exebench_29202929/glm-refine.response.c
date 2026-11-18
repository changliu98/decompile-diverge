char *__cdecl mystpcpy(char *to, const char *from)
{
  while ((*to++ = *from++) != '\0')
    ;

  return --to;
}