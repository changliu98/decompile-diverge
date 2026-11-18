char *__cdecl strcpy(char *dest, const char *src)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax
  char *d; // [rsp+0h] [rbp-18h]

  d = dest;
  while ( *src )
  {
    v2 = src++;
    v3 = *v2;
    v4 = d++;
    *v4 = v3;
  }
  *d = 0;
  return dest;
}