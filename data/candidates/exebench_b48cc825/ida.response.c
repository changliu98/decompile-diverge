char *__cdecl strcpy(char *s1, const char *s2)
{
  const char *v2; // rax
  char *v3; // rcx
  char *s1a; // [rsp+14h] [rbp-8h]

  s1a = s1;
  do
  {
    v2 = s2++;
    LOBYTE(v2) = *v2;
    v3 = s1a++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  return s1;
}