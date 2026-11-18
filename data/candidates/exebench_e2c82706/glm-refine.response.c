char *__cdecl strCpy(char *dest, const char *src)
{
  char *dest_start = dest;
  char current_char;

  do
  {
    current_char = *src++;
    *dest_start++ = current_char;
  }
  while (current_char);

  return dest;
}