char *__cdecl strcpy(char *dest, const char *src)
{
  size_t i; // [rsp+0h] [rbp-14h]

  for ( i = 0; src[i]; ++i )
    dest[i] = src[i];
  dest[i] = '\0';
  
  return dest;
}