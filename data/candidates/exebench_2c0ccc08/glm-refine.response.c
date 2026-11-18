char *__cdecl strcpy2(char *s, const char *t)
{
  char *sa = s;

  do
  {
    *sa++ = *t;
  }
  while (*t++);

  return s;
}