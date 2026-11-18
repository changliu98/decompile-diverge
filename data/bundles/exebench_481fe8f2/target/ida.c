char *__cdecl strcpy2(char *dst, const char *src)
{
  const char *v2; // rax
  char *v3; // rcx
  char *dsta; // [rsp+14h] [rbp-8h]

  dsta = dst;
  do
  {
    v2 = src++;
    LOBYTE(v2) = *v2;
    v3 = dsta++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  return dst;
}