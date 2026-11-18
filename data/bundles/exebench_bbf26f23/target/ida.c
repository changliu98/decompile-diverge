char *__cdecl strcpy(char *dest, const char *src)
{
  unsigned int size; // [rsp+0h] [rbp-14h]

  for ( size = 0; src[size]; ++size )
    dest[size] = src[size];
  dest[size] = 0;
  return dest;
}