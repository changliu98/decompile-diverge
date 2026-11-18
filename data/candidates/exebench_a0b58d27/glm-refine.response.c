char *__cdecl string_copy(char *dest, const char *src)
{
  char *d;

  if ( !src || !dest )
    return NULL;

  d = dest;
  while ( *src )
  {
    *d++ = *src++;
  }
  *d = '\0';
  
  return dest;
}