char *__cdecl strcpy(char *dst, const char *src)
{
  char *start = dst;
  char current_char;

  do
  {
    current_char = *src++;
    *dst++ = current_char;
  }
  while (current_char);

  return start;
}