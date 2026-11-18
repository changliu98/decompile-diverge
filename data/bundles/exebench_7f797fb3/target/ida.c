char *__cdecl strcpy(char *dst, const char *src)
{
  const char *v2; // rax
  char *v3; // rcx
  char *tmp; // [rsp+0h] [rbp-18h]

  tmp = dst;
  do
  {
    v2 = src++;
    LOBYTE(v2) = *v2;
    v3 = tmp++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  return dst;
}