void __cdecl lemon_strcpy(char *dest, const char *src)
{
  char c;

  do
  {
    c = *src++;
    *dest++ = c;
  }
  while (c);
}