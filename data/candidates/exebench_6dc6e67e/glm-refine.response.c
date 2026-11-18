void __cdecl copia(char *dest, const char *source)
{
  while (*source)
  {
    *dest++ = *source++;
  }
  *dest = '\0';
}