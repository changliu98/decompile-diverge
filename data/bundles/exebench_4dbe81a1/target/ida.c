char *__cdecl GO_strcpy(char *d, char *s)
{
  char *v2; // rax
  char *v3; // rcx
  char *da; // [rsp+10h] [rbp-8h]

  da = d;
  do
  {
    v2 = s++;
    LOBYTE(v2) = *v2;
    v3 = da++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  return d;
}