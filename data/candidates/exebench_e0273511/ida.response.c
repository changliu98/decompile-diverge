char *__cdecl strcpy(char *dest, const char *src)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax
  char *pdest; // [rsp+8h] [rbp-18h]

  pdest = dest;
  while ( *src )
  {
    v2 = src++;
    v3 = *v2;
    v4 = pdest++;
    *v4 = v3;
  }
  *pdest = 0;
  return dest;
}