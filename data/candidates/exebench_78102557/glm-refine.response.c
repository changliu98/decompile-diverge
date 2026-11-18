char *__cdecl strcpy(char *s1, const char *s2)
{
  char *dest = s1;

  do
  {
    *dest++ = *s2;
  }
  while (*s2++);

  return s1;
}