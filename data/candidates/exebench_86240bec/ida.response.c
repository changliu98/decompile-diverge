char *__cdecl ft_strcpy(char *dst, const char *src)
{
  const char *v2; // rax
  char *v3; // rcx
  char *d; // [rsp+0h] [rbp-18h]

  d = dst;
  do
  {
    v2 = src++;
    LOBYTE(v2) = *v2;
    v3 = d++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  return dst;
}