char *__cdecl strcpy(char *dest, const char *src)
{
  char *original_dest = dest;
  char current_char;

  do
  {
    current_char = *src++;
    *dest++ = current_char;
  }
  while (current_char);

  return original_dest;
}