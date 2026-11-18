char *__cdecl pat_strcpy(char *s1, char *s2)
{
  char *v2; // rax
  char *v3; // rcx

  do
  {
    v2 = s2++;
    LOBYTE(v2) = *v2;
    v3 = s1++;
    *v3 = (char)v2;
  }
  while ( (_BYTE)v2 );
  return s1 - 1;
}