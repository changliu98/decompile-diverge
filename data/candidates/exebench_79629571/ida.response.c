char *__cdecl ft_strcpy(char *dst, const char *src)
{
  const char *v2; // rax
  char *v3; // rcx
  char *dsta; // [rsp+10h] [rbp-8h]

  dsta = dst;
  do
  {
    v2 = src++;
    LOBYTE(v2) = *v2;
    v3 = dsta++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  *dsta = 0;
  return dst;
}