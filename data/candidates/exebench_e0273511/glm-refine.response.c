char *__cdecl strcpy(char *dest, const char *src)
{
  char *pdest = dest;
  
  while ( *src )
  {
    *pdest++ = *src++;
  }
  
  *pdest = 0;
  return dest;
}