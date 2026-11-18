char *__cdecl strcpy(char *destination, const char *source)
{
  char *d = destination;
  
  while (*source)
  {
    *d++ = *source++;
  }
  
  *d = '\0';
  return destination;
}