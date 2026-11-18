char *__cdecl strcpy(char *dst, const char *src)
{
  size_t v2; // rcx
  size_t i; // [rsp+0h] [rbp-18h]

  i = 0LL;
  do
  {
    dst[i] = src[i];
    v2 = i++;
  }
  while ( src[v2] );
  return dst;
}