char *__cdecl GO_strcpy(char *d, char *s)
{
  char *da = d;
  char c;

  do
  {
    c = *s++;
    *da++ = c;
  }
  while (c);

  return d;
}