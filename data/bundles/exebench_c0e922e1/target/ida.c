char *__cdecl strcpy(char *destination, const char *s)
{
  const char *v2; // rax
  char v3; // cl
  char *v4; // rax
  char *d; // [rsp+0h] [rbp-18h]

  d = destination;
  while ( *s )
  {
    v2 = s++;
    v3 = *v2;
    v4 = d++;
    *v4 = v3;
  }
  *d = 0;
  return destination;
}