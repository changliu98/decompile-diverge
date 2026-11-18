char *__cdecl my_strcpy(char *dest, const char *src)
{
  char *dest_start = dest;
  char current_char;

  do
  {
    current_char = *src++;
    *dest++ = current_char;
  }
  while (current_char);

  return dest_start;
}