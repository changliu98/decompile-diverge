char *__cdecl strcpy2(char *s, const char *t)
{
  const char *v2; // rax
  char *v3; // rcx
  char *sa; // [rsp+10h] [rbp-8h]

  sa = s;
  do
  {
    v2 = t++;
    LOBYTE(v2) = *v2;
    v3 = sa++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  return s;
}