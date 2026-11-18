char *__cdecl strcpy(char *s1, const char *s2)
{
  char *s1a = s1;

  do
  {
    *s1a++ = *s2;
  }
  while (*s2++);

  return s1;
}