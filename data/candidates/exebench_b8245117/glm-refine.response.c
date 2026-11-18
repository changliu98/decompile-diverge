char *__cdecl mystrcpy(char *dest, char *src)
{
  char *desta = dest;
  
  while (*src)
  {
    *desta++ = *src++;
  }
  
  *desta = '\0';
  return dest;
}